#import <UIKit/UIKit.h>

@interface CTViewController : UIViewController
@property IBOutlet UITextField *productNameField, *productPriceField;

- (IBAction)makePayment:(id)aSender;
@end
