//
//  CTAppDelegate.h
//  Coiney Test
//
//  Created by Fjölnir Ásgeirsson on 7/29/13.
//  Copyright (c) 2013 Coiney. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CTViewController;

@interface CTAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) CTViewController *viewController;

@end
