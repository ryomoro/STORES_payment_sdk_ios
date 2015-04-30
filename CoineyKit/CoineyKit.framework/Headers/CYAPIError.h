// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>

@interface CYAPIError : NSError
@property(nonatomic, readonly) NSString *cy_localizedDescription;
@property(nonatomic, readonly) NSString *cy_localizedTitle;
@end
