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

@end
