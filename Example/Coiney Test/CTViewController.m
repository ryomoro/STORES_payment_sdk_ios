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

    CYLineItem *lineItem = [CYLineItem itemWithAmount:price
                                             currency:CYCurrencyJPY
                                                 name:name];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[lineItem]];
    coineyController.delegate = self;
    
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);

    [self dismissViewControllerAnimated:YES completion:nil];
    
    CYTransactionViewController *transactionViewController =
        [CYTransactionViewController transactionViewControllerWithTransaction:aTransaction
                                                               allowRefunding:YES]; // Pass NO to hide the refund button
    
    [self.navigationController pushViewController:transactionViewController animated:YES];
}

- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
