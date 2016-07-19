// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>

/// \~english
/// Enables or disables receipt printing from CoineyKit. Disabled by default.
/// \param aFlag YES to enable, NO to disable
/// \~japanese
/// 決済完了画面、および取引詳細画面のレシート印刷機能オン・オフを切り替えます。デフォルトはオフです。
/// \param aFlag 有効化する場合はYES、無効化する場合はNO
void CYEnablePrinting(BOOL aFlag);
