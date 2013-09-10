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
@property(readonly) NSString *identifier;
/// \~english
/// Returns the date/time of the transaction
@property(readonly) NSDate *chargeDate;
/// \~english
/// The currency of the transaction amount
@property(readonly) CYCurrency currency;
/// \~english
/// The amount of the transaction in its currency
@property(readonly) NSNumber *amount;
/// \~english
/// The brand of credit card used to make the transaction
@property(readonly) CYCardBrand cardBrand;
/// \~english
/// Returns a string containing the last 4 digits of the credit card's number
@property(readonly) NSString *cardSuffix;
/// \~english
/// Returns whether or not the transaction has been refunded
@property(readonly) BOOL isRefunded;
/// \~english
/// Returns the date/time the transaction was refunded (or nil if it has not been refunded)
@property(readonly) NSDate *refundDate;
@end