// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <CoreData/CoreData.h>
#import <CoineyKit/CYTypes.h>
#import <CoineyKit/CYTransaction.h>

@protocol CYEmoneyTransaction <CYTransaction>

@property(nonatomic, readonly, nullable) NSDate *unconfirmedDate; // better name??
@property(nonatomic, readonly, getter=isUnconfirmed) BOOL unconfirmed;

@property(nonatomic, readonly, nullable) NSNumber *initialCardBalance;
@property(nonatomic, readonly, nullable) NSNumber *finalCardBalance;
@property(nonatomic, readonly) CYEmoneyBrand emoneyBrand;
@property(nonatomic, readonly, nullable) NSString *cardNumber;
@property(nonatomic, readonly, nullable) NSString *thincaDeviceIdentifier;
@property(nonatomic, readonly, nullable) NSString *sprwid;
@property(nonatomic, readonly, nullable) NSString *thincaDealNumber;

@end

