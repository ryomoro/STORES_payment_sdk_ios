// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>

@class CYCoineyViewController, CYTransaction;

/// \~english
/// A Delegate for CYCoineyViewController
@protocol CYCoineyViewControllerDelegate <NSObject>
@optional
/// \~english
/// Called when the user has entered his username/password and logged in.
/// If the users's credentials were saved and there was no need to show the login screen
/// then this method is never called.
/// @param aController The originating Coiney controller
- (void)coineyViewControllerDidAuthenticate:(CYCoineyViewController *)aController;

/// \~english
/// Called when the user completes a transaction.
/// @param aController The originating Coiney controller
/// @param aTransaction The transaction object
- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(CYTransaction *)aTransaction;

/// \~english
/// Called if the user hits cancel without completing a transaction.
/// @param aController The originating Coiney controller
- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController;
@end

/// \~english
/// CYCoineyViewController is an all-in-one controller that
/// handles the entire process of making a payment using Coiney.
@interface CYCoineyViewController : UIViewController
@property(weak) id<CYCoineyViewControllerDelegate> delegate;

/// \~english
/// Returns an initialized controller
/// @param aLineItems The line items to pre-populate the product entry view with
- (id)initWithLineItems:(NSArray *)aLineItems;
@end
