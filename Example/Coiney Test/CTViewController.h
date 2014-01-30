#import <UIKit/UIKit.h>

@interface CTViewController : UIViewController
@property(weak, nonatomic) IBOutlet UITextField *productNameField, *productPriceField;

- (IBAction)makePayment:(id)aSender;
@end
