// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

@import Foundation;
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a single line item (product) in a transaction.
/// \~japanese
/// 決済内訳の一項目（商品）を表します。
@interface CYLineItem : NSObject
/// \~english
/// The currency of the item
/// \~japanese
/// 項目価格の通貨
@property(readonly) CYCurrency currency;
/// \~english
/// The price of the item in its currency
/// \~japanese
/// 価格
@property(readonly) double amount;
/// \~english
/// The name of the product
/// \~japanese
/// 品名
@property(readonly) NSString *name;

/// \~english
/// Returns a pre-initialized line item.
/// \param aAmount The price of the item
/// \param aCurrency The currency in which the price is represented
/// \param aName The name of the item
/// \~japanese
/// 初期化済みの項目を返します。
/// \param aAmount  価格
/// \param aCurrency 通貨
/// \param aName 品名
+ (instancetype)itemWithAmount:(NSUInteger)aAmount
                      currency:(CYCurrency)aCurrency
                          name:(NSString *)aName;
@end
