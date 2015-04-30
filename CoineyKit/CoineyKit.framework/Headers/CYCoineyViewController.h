// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>
#import <CoineyKit/CYTransaction.h>
#import <CoineyKit/CYContainerViewController.h>

@class CYCoineyViewController;

/// \~english
/// A Delegate for CYCoineyViewController
/// \~japanese
/// `CYCoineyViewController` のデリゲート
@protocol CYCoineyViewControllerDelegate <NSObject>
@optional
/// \~english
/// Called when the controller is on screen and ready to process
/// transactions.
/// \~japanese
/// `CYCoineyViewController` が表示された時点で呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
- (void)coineyViewControllerDidBecomeReady:(CYCoineyViewController *)aController;

/// \~english
/// Called when the user completes a transaction.
/// \param aController The originating Coiney controller
/// \param aTransaction The transaction object
/// \~japanese
/// ユーザーが決済を完了した際に呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
/// \param aTransaction 完了した決済オブジェクト
- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction;

/// \~english
/// Called if the user hits cancel without completing a transaction.
/// \param aController The originating Coiney controller
/// \~japanese
/// ユーザーが決済をキャンセルした際に呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController;
@end

/// \~english
/// `CYCoineyViewController` is an all-in-one controller that
/// handles the entire process of making a payment using Coiney.
/// \~japanese
/// コイニーによる一連の決済フローを提供します。
@interface CYCoineyViewController : CYContainerViewController
@property(nonatomic, weak) id<CYCoineyViewControllerDelegate> delegate;

/// \~english
/// Returns an initialized controller
/// \param aLineItems The line items to pre-populate the product entry view with
/// \~japanese
/// 項目で初期化された `CYCoineyViewController` を返します。
/// \param aLineItems 初期化するための項目一覧
- (instancetype)initWithLineItems:(NSArray *)aLineItems;
@end
