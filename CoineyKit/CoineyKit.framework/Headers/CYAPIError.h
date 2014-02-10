// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

@import Foundation;

@interface CYAPIError : NSError
@property(readonly) NSString *cy_localizedDescription;
@property(readonly) NSString *cy_localizedTitle;
@end
