// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <CoreData/CoreData.h>
#import <CoineyKit/CYTypes.h>
#import <CoineyKit/CYTransaction.h>

/// \~english
/// Represents a transaction made through Coiney.
///
/// **Warning** Do not attempt to pass custom `CYTransaction` conforming classes to CoineyKit.
/// \~japanese
/// 一つの決済を表します。
///
/// **注** `CYTransaction` プロトコルを適用したカスタムクラスを CoineyKit に渡さないこと。
@protocol CYWechatPayTransaction <CYTransaction>
/// \~english
/// Returns the date/time of the refund, or nil if not refunded.
/// \~japanese
/// 返品の日時（未返品であればnil）
@property(nonatomic, readonly, nullable) NSDate *refundDate;
/// \~english
/// Returns whether or not the transaction has been refunded
/// \~japanese
/// 返品済みかどうか
@property(nonatomic, readonly, getter=isRefunded) BOOL refunded;

@end
