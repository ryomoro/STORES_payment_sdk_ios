#import "CTAppDelegate.h"
@import CoineyKit;

@implementation CTAppDelegate
- (BOOL)          application:(UIApplication *)aApplication
didFinishLaunchingWithOptions:(NSDictionary *)aOptions
{
    CYEnablePrinting(YES);
    [CYKit setEnableSendReceipt: YES];
    return YES;
}
@end
