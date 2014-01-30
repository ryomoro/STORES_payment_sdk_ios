// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

@import UIKit;
#import <CoineyKit/CYTransaction.h>
@class CYCoineyViewController;

/// \~english
/// A Delegate for CYCoineyViewController
/// \~japanese
/// `CYCoineyViewController` のデリゲート
@protocol CYCoineyViewControllerDelegate <NSObject>
@optional
/// \~english
/// Called when the user has entered his username/password and logged in.
/// If the users's credentials were saved and there was no need to show the login screen
/// then this method is never called.
/// \param aController The originating Coiney controller
/// \~japanese
/// ユーザーがメールアドレスとパスワードを入力し、ログインした際に呼ばれます。
/// 前回のログイン情報が保持され、ログインが省略された場合は、呼ばれません。
/// \param aController 呼び出し元の `CYCoineyViewController`
- (void)coineyViewControllerDidAuthenticate:(CYCoineyViewController *)aController;

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
@interface CYCoineyViewController : UIViewController
@property(weak) id<CYCoineyViewControllerDelegate> delegate;

/// \~english
/// Returns an initialized controller
/// \param aLineItems The line items to pre-populate the product entry view with
/// \~japanese
/// 項目で初期化された `CYCoineyViewController` を返します。
/// \param aLineItems 初期化するための項目一覧
- (id)initWithLineItems:(NSArray *)aLineItems;
@end
