// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <CoreData/CoreData.h>
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a transaction made through Coiney.
///
/// **Warning** Do not attempt to pass custom `CYTransaction` conforming classes to CoineyKit.
/// \~japanese
/// 一つの決済を表します。
///
/// **注** `CYTransaction` プロトコルを適用したカスタムクラスを CoineyKit に渡さないこと。
@protocol CYCreditCardTransaction <CYTransaction>


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


/// \~english
/// The brand of credit card used to make the transaction. \ref CYUnknownCardBrand for WeChat Pay
/// transactions.
/// \~japanese
/// 決済に使われたカードブランド。WeChat Pay決済では \ref CYUnknownCardBrand
@property(nonatomic, readonly) CYCardBrand cardBrand;
/// \~english
/// Returns a string containing the last 4 digits of the credit card's number. `nil` for WeChat Pay
/// transactions.
/// \~japanese
/// カード番号の下4桁。WeChat Pay決済では `nil`
@property(nonatomic, readonly, nullable) NSString *cardSuffix;
/// \~english
/// Method of credit card financing (installments, revolving, etc.) \ref CYFinancingNone for WeChat
/// Pay transactions.
/// \~japanese
/// 支払区分。WeChat Pay決済では \ref CYFinancingNone
@property(nonatomic, readonly) CYFinancingType financing;

/// \~english
/// Returns the approval code from the acquirer
/// \~japanese
/// アクワイアラが発行する承認コード。WeChat Pay決済では `nil`
@property(nonatomic, readonly, nullable) NSString *approvalCode;
/// \~english
/// Returns the AID for an IC card transaction. `nil` for magstripe credit card and WeChat Pay
/// transactions.
/// \~japanese
/// ICカード決済のAID。磁気カード決済およびWeChat Pay決済では `nil`
@property(nonatomic, readonly, nullable) NSString *applicationIdentifier;
/// \~english
/// Returns the application label for an IC card transaction. `nil` for magstripe credit card and
/// WeChat Pay transactions.
/// \~japanese
/// ICカード決済のアプリケーションラベル。磁気カード決済およびWeChat Pay決済では `nil`
@property(nonatomic, readonly, nullable) NSString *applicationLabel;
/// \~english
/// Returns the card network device identifier.
/// \~japanese
/// 端末識別番号
@property(nonatomic, readonly, nullable) NSString *cardNetworkDeviceIdentifier;

@end

