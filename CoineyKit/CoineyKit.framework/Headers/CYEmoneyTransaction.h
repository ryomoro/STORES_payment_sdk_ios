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
@protocol CYEmoneyTransaction <CYTransaction>

/// \~english
/// Returns the date/time of the unconfirmed, or nil if not unconfirmed.
/// \~japanese
/// 処理未了の日時（処理未了が無ければnil）
@property(nonatomic, readonly, nullable) NSDate *unconfirmedDate; // better name??

/// \~english
/// Returns whether or not the transaction has been unconfirmed
/// \~japanese
/// 処理未了かどうか
@property(nonatomic, readonly, getter=isUnconfirmed) BOOL unconfirmed;

/// \~english
/// Returns card balance before payment
/// \~japanese
/// 決済前カード残高
@property(nonatomic, readonly, nullable) NSNumber *initialCardBalance;
/// \~english
/// Returns card balance after payment
/// \~japanese
/// 決済後カード残高
@property(nonatomic, readonly, nullable) NSNumber *finalCardBalance;
/// \~english
/// Returns card brand
/// \~japanese
/// カードブランド
@property(nonatomic, readonly) CYEmoneyBrand emoneyBrand;
/// \~english
/// Returns card number
/// \~japanese
/// カードナンバー
@property(nonatomic, readonly, nullable) NSString *cardNumber;
/// \~english
/// Returns device identifier
/// \~japanese
/// 端末番号
@property(nonatomic, readonly, nullable) NSString *thincaDeviceIdentifier;
/// \~english
/// Returns SPRWID
/// \~japanese
/// SPRWID
@property(nonatomic, readonly, nullable) NSString *sprwid;
/// \~english
/// Returns deal number
/// \~japanese
/// 問合番号
@property(nonatomic, readonly, nullable) NSString *thincaDealNumber;

@end
