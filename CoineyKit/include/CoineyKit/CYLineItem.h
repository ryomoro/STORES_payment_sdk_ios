// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a single line item (product) in a transaction
@interface CYLineItem : NSObject
/// \~english
/// The currency of the item
@property CYCurrency currency;
/// \~english
/// The price of the item in its currency
@property(nonatomic) double amount;
/// \~english
/// The name of the product
@property(copy) NSString *name;

/// \~english
/// Returns a pre-initialized line item.
/// @param aAmount the price of the item
/// @param aCurrency the currency in which the price is represented
/// @param aName the name of the item
+ (instancetype)itemWithAmount:(NSUInteger)aAmount
                      currency:(CYCurrency)aCurrency
                          name:(NSString *)aName;
@end