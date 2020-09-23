#import "CTViewController.h"
@import CoineyKit;

@interface CTViewController () <CYCoineyViewControllerDelegate>
@end

@implementation CTViewController

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    [CYKit prepareInController:self];
}

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productNameField.text;
    NSInteger amount = [_productPriceField.text integerValue];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:amount memo:memo];
    coineyController.delegate = self;
    
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (IBAction)deauthenticate:(id)aSender
{
    [CYAuthenticationViewController deauthenticate];
}

- (void)convertTransaction:(id<CYTransaction>)aTransaction {
    if ( [aTransaction conformsToProtocol:@protocol(CYCreditCardTransaction)] ) {
        id<CYCreditCardTransaction> cardTransaction = (id<CYCreditCardTransaction>)aTransaction;
        NSLog(@"Credit Card%@", cardTransaction);
    } else if ( [aTransaction conformsToProtocol:@protocol(CYWechatPayTransaction)] ) {
        id<CYWechatPayTransaction> wechatPayTransaction = (id<CYWechatPayTransaction>)aTransaction;
        NSLog(@"WeChatPay %@", wechatPayTransaction);
    }  else if ( [aTransaction conformsToProtocol:@protocol(CYEmoneyTransaction)] ) {
        id<CYEmoneyTransaction> emoneyTransaction = (id<CYEmoneyTransaction>)aTransaction;
        NSLog(@"Emoney %@", emoneyTransaction);
    }
}

- (void)lookUpTransaction:(NSString *)transactionId {
    CYLookUpTransaction(transactionId, ^(id<CYTransaction> transaction, NSError *error) {
        if(!transaction) {
            NSLog(@"Transaction ID %@ doesn't exist! Wrong account, maybe?", transactionId);
        } else {
            [self convertTransaction:transaction];
        }
    });
}

- (void)lookUpEmoneyTransaction:(NSString *)transactionId {
    CYLookUpEmoneyTransaction(transactionId, ^(id<CYTransaction> transaction, NSError *error) {
        if(!transaction) {
            NSLog(@"Transaction ID %@ doesn't exist! Wrong account, maybe?", transactionId);
        } else {
            [self convertTransaction:transaction];
        }
    });
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);

    if ( [aTransaction conformsToProtocol:@protocol(CYEmoneyTransaction)] ) {
        [self lookUpEmoneyTransaction:aTransaction.identifier];
    } else {
        [self lookUpTransaction:aTransaction.identifier];
    }

    [self dismissViewControllerAnimated:YES completion:^{
        CYTransactionViewController *transactionViewController =
            [CYTransactionViewController transactionViewControllerWithTransaction:aTransaction
                                                                   allowRefunding:YES]; // Pass NO to hide the refund button
        transactionViewController.navigationItem.rightBarButtonItem =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                          target:self
                                                          action:@selector(coineyViewControllerDidCancel:)];
        UINavigationController *navigationController =
            [[UINavigationController alloc] initWithRootViewController:transactionViewController];
        navigationController.modalPresentationStyle = UIModalPresentationFormSheet;
        [self presentViewController:navigationController animated:YES completion:nil];
    }];
}

- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}
@end
