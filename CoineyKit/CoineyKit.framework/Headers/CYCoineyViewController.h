// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>
#import <CoineyKit/CYTransaction.h>
#import <CoineyKit/CYContainerViewController.h>
#import <CoineyKit/CYTypes.h>

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
- (void)coineyViewControllerDidBecomeReady:(CYCoineyViewController * _Nonnull)aController;

/// \~english
/// Called when the user completes a transaction.
/// \param aController The originating Coiney controller
/// \param aTransaction The transaction object
/// \~japanese
/// ユーザーが決済を完了した際に呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
/// \param aTransaction 完了した決済オブジェクト
- (void)coineyViewController:(CYCoineyViewController * _Nonnull)aController
      didCompleteTransaction:(id<CYTransaction> _Nonnull)aTransaction;

/// \~english
/// Called if the user hits cancel without completing a transaction.
/// \param aController The originating Coiney controller
/// \~japanese
/// ユーザーが決済をキャンセルした際に呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
- (void)coineyViewControllerDidCancel:(CYCoineyViewController * _Nonnull)aController;

/// \~english
/// Called when it is unknown whether the card was successfully charged.
/// \param aController The originating Coiney controller
/// \~japanese
/// 交通系電子マネーで引き去り処理の成否が不明な場合に呼ばれます。
/// \param aController 呼び出し元の `CYCoineyViewController`
- (void)         coineyViewController:(CYCoineyViewController * _Nonnull)aController
didCompleteWithUnconfirmedTransaction:(id<CYTransaction> _Nonnull)aTransaction;
@end

/// \~english
/// `CYCoineyViewController` is an all-in-one controller that
/// handles the entire process of making a payment using Coiney.
/// \~japanese
/// コイニーによる一連の決済フローを提供します。
@interface CYCoineyViewController : CYContainerViewController
@property(nonatomic, weak, nullable) id<CYCoineyViewControllerDelegate> delegate;

/// \~english
/// Returns an initialized controller.
/// \param aAmount The total amount to pay. Must be between kCYMinAmount and kCYMaxAmount.
/// \param aMemo An optional description.
/// \~japanese
/// `CYCoineyViewController` を生成して返します。
/// \param aAmount 決済額 (kCYMinAmount、kCYMaxAmount の範囲内で指定)
/// \param aMemo 決済のメモ
- (instancetype _Nonnull)initWithAmount:(int64_t)aAmount memo:(NSString * _Nullable)aMemo;

/// \~english
/// Returns an initialized controller.
/// \param aAmount The total amount to pay. Must be between kCYMinAmount and kCYMaxAmount.
/// \param aMemo An optional description.
/// \param aPaymentMethod A payment method.
/// \~japanese
/// `CYCoineyViewController` を生成して返します。
/// \param aAmount 決済額 (kCYMinAmount、kCYMaxAmount の範囲内で指定)
/// \param aMemo 決済のメモ
/// \param aPaymentMethod 決済方法
- (instancetype _Nonnull)initWithAmount:(int64_t)aAmount
                          memo:(NSString * _Nullable)aMemo
                 paymentMethod:(CYPaymentMethod)aPaymentMethod;

@end

/// \~english
/// Returns a bitmask representing the merchant's accepted payment methods, or 0 if unauthenticated.
/// \~japanese
/// ログイン中の加盟店で利用可能な決済方法を返します。未ログインの場合は0を返します。
CYPaymentMethodMask CYAcceptedPaymentMethods(void);
