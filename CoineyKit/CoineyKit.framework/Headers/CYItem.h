// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a single item (product) in a transaction.
/// \~japanese
/// 決済内訳の一項目（商品）を表します。
@interface CYItem : NSObject
/// \~english
/// The currency of the item
/// \~japanese
/// 項目価格の通貨
@property(nonatomic, readonly) CYCurrency currency;
/// \~english
/// The total price of the item in its currency
/// \~japanese
/// 合計額
@property(nonatomic, readonly) int64_t total;
/// \~english
/// The unit price of the item in its currency
/// \~japanese
/// 単価
//@property(nonatomic, readonly) int64_t unitPrice;
/// \~english
/// The quantity of the item
/// \~japanese
/// 数量
//@property(nonatomic, readonly) int64_t *quantity;
/// \~english
/// The name of the product
/// \~japanese
/// 品名
@property(nonatomic, readonly) NSString *name;


/// \~english
/// Returns a pre-initialized item.
/// \param aAmount The price of the item
/// \param aCurrency The currency in which the price is represented
/// \param aName The name of the item
/// \~japanese
/// 初期化済みの項目を返します。
/// \param aAmount  価格
/// \param aCurrency 通貨
/// \param aName 品名
+ (instancetype)itemWithTotal:(NSUInteger)aTotal
                     currency:(CYCurrency)aCurrency
                         memo:(NSString *)aMemo;

/// \~english
/// Returns a pre-initialized line item with a unit price and quantity.
/// \param aAmount The price of the item
/// \param aQuantity The quantity of the item
/// \param aCurrency The currency in which the price is represented
/// \param aName The name of the item
/// \~japanese
/// 単価、数量を初期化済みの項目を返します。
/// \param aAmount  単価
/// \param aQuantity 数量
/// \param aCurrency 通貨
/// \param aName 品名
+ (instancetype)itemWithUnitPrice:(NSUInteger)aUnitPrice
                         quantity:(NSUInteger)aQuantity
                         currency:(CYCurrency)aCurrency
                             memo:(NSString *)aMemo;
@end
