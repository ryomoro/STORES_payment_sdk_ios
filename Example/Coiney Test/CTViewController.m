#import "CTViewController.h"
@import CoineyKit;

@interface CTViewController () <CYCoineyViewControllerDelegate>
@end

@implementation CTViewController

- (IBAction)makePayment:(id)aSender
{
    // Create a line item to pre-populate the Coiney controller with.
    NSString *name = _productNameField.text;
    NSInteger price = [_productPriceField.text integerValue];

    CYItem *lineItem = [CYItem itemWithTotal:price
                                    currency:CYCurrencyJPY
                                        memo:name];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[lineItem]];
    coineyController.delegate = self;
    
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (IBAction)deauthenticate:(id)aSender
{
    [CYAuthenticationViewController deauthenticate];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);

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
