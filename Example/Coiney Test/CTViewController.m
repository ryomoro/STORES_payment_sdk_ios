#import "CTViewController.h"
#import <CoineyKit/CoineyKit.h>

@interface CTViewController () <CYCoineyViewControllerDelegate>  // ←
@end                                                             // ←

@implementation CTViewController

- (IBAction)makePayment:(id)aSender
{
    // Create a line item to pre-populate the Coiney controller with.
    NSString *name = _productNameField.text;
    int price = [_productPriceField.text intValue];
    
    CYLineItem *lineItem = [CYLineItem itemWithAmount:price
                                             currency:CYCurrencyJPY name:name];
    
    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[lineItem]];
    coineyController.delegate = self; // ←
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController  // ←
      didCompleteTransaction:(CYTransaction *)aTransaction          // ←
{
    NSLog(@"Completed transaction!: %@", aTransaction);             // ←
}

- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController  // ←
{
    NSLog(@"Cancelled payment.");                                            // ←
}

@end
