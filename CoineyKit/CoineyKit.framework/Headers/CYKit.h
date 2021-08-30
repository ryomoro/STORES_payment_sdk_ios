// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CYKit : NSObject

/// \~english
/// Returns if the emoney initialization is complete.
/// \~japanese
/// 電子マネーの初期化が完了しているかを返します。
+ (BOOL)emoneyInitialized;

/// \~english
/// The initial preparation of the CoineyKit.
/// \~japanese
/// CoineyKitの初期準備をします。
/// 初期化のエラーダイアログはKeyWindowのrootViewControllerに表示されます
+ (void)prepare;

/// \~english
/// The initial preparation of the CoineyKit.
/// \~japanese
/// CoineyKitの初期化準備をします。
/// \param controller  初期化のエラーダイアログを表示するコントローラー。nil を渡すとKeyWindowのrootViewControllerに表示されます
+ (void)prepareInController:(nullable UIViewController *)controller;

/// \~english
/// The initial preparation of the CoineyKit for Semi-self checkout mode.
/// \~japanese
/// セミ セルフレジモードでCoineyKitの初期準備をします。
/// 初期化のエラーダイアログはKeyWindowのrootViewControllerに表示されます
+ (void)prepareForSemiSelfCheckoutMode;

/// \~english
/// The initial preparation of the CoineyKit for Semi-self checkout mode.
/// \~japanese
/// セミ セルフレジモードCoineyKitの初期化準備をします。
/// \param controller  初期化のエラーダイアログを表示するコントローラー。nil を渡すとKeyWindowのrootViewControllerに表示されます
+ (void)prepareForSemiSelfCheckoutModeInController:(nullable UIViewController *)controller;

/// \~english
/// Set display / non-display of the email address input field for sending receipts at payment is completed view. The default is YES (true).
/// \~japanese
/// 決済完了時にレシート送信のメールアドレス入力フィールドの表示 / 非表示を設定します。デフォルト は YES (true)です。
/// \param enabled レシート送信メールアドレス入力フィールドの表示 / 非表示 設定
+ (void)setEnableSendReceipt:(BOOL)enable;

/// \~english
/// Display / non-display setting status of the email address input field for sending receipts.
/// \~japanese
/// レシート送信のメールアドレス入力フィールドの表示 / 非表示の状態
+ (BOOL)isSendReceiptEnabled;

/// \~english
/// Semi-self checkout mode setting status.
/// \~japanese
/// セミ セルフレジ モードの設定状態を返します。
+ (BOOL)isSemiSelfCheckoutMode;

@end
