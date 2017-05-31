// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>

@interface CYContainerViewController : UIViewController
@property(nonatomic, strong, nullable) UIViewController *containedViewController;
- (void)setContainedViewController:(UIViewController * _Nonnull)aController
                          animated:(BOOL)aAnimated;
- (void)setContainedViewController:(UIViewController * _Nonnull)aController
                          animated:(BOOL)aAnimated
                        completion:(void (^_Nullable)(void))aBlock;
@end

@interface CYContainmentSegue : UIStoryboardSegue
@end
