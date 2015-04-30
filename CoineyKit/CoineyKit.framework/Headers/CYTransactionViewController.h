// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>
#import <CoineyKit/CYTransaction.h>

/// \~english
/// `CYTransactionViewController` displays the details of a transaction.
/// \~japanese
/// 決済詳細画面のビューコントローラです。
@interface CYTransactionViewController : UIViewController

/// \~english
/// The transaction object of the controller
/// \~japanese
/// コントローラの決済オブジェクト
@property(nonatomic, readonly, nonatomic) id<CYTransaction> transaction;

/// \~english
/// Whether refunding is allowed
/// \~japanese
/// 返品可能かどうか
@property(nonatomic, readonly, nonatomic, getter=allowsRefunding) BOOL allowRefunding;

/// \~english
/// Returns a controller populated with the information from `aTransaction`
/// \param aTransaction The transaction of the controller
/// \param aAllowRefunds Whether refunding should be allowed
/// \~japanese
/// 特定の決済の詳細画面を返します。
/// \param aTransaction コントローラに設定する `CYTransaction` オブジェクト
/// \param aAllowRefunds 返品可能にするかどうか
+ (instancetype)transactionViewControllerWithTransaction:(id<CYTransaction>)aTransaction
                                          allowRefunding:(BOOL)aAllowRefunds;
@end
