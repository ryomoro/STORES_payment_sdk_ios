// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>

@interface CYContainerViewController : UIViewController
@property(nonatomic, strong) UIViewController *containedViewController;
- (void)setContainedViewController:(UIViewController *)aController animated:(BOOL)aAnimated;
- (void)setContainedViewController:(UIViewController *)aController
                          animated:(BOOL)aAnimated
                        completion:(void (^)(void))aBlock;
@end

@interface CYContainmentSegue : UIStoryboardSegue
@end
