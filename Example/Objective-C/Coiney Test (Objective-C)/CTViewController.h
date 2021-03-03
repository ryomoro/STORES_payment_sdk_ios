#import <UIKit/UIKit.h>

@interface CTViewController : UIViewController
@property(weak, nonatomic) IBOutlet UITextField *memoTextField, *priceTextField;

- (IBAction)makePayment:(id)aSender;
- (IBAction)deauthenticate:(id)aSender;
@end
