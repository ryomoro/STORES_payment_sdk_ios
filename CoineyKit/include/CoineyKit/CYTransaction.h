// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <CoreData/CoreData.h>
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a transaction made through coiney
@interface CYTransaction : NSObject
/// \~english
/// A unique transaction identifier
@property(nonatomic, readonly) NSString *identifier;
/// \~english
/// Returns the date/time of the transaction
@property(nonatomic, readonly) NSDate *chargeDate;
/// \~english
/// The currency of the transaction amount
@property(nonatomic, readonly) CYCurrency currency;
/// \~english
/// The amount of the transaction in its currency
@property(nonatomic, readonly) NSNumber *amount;
/// \~english
/// The brand of credit card used to make the transaction
@property(nonatomic, readonly) CYCardBrand cardBrandUsed;
/// \~english
/// Returns a string containing the last 4 digits of the credit card's number
@property(nonatomic, readonly) NSString *cardSuffix;
/// \~english
/// Returns whether or not the transaction has been refunded
@property(nonatomic, readonly) BOOL isRefunded;
/// \~english
/// Returns the date/time the transaction was refunded (or nil if it has not been refunded)
@property(nonatomic, readonly) NSDate *refundDate;
@end