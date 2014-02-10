// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

@import Foundation;

/// \~english
/// Represents a currency.
/// (Currently only Japanese Yen are supported)
/// \~japanese
/// 通貨を表します。
/// (現在日本円のみ対応)
typedef NS_ENUM(NSInteger, CYCurrency) {
    /// \~english
    /// Invalid currency code
    /// \~japanese
    /// 不正な通貨コード
    CYCurrencyInvalid,
    /// \~english
    /// Japanese Yen
    /// \~japanese
    /// 日本円
    CYCurrencyJPY
};

/// \~english
/// Represents a brand of credit card.
/// \~japanese
/// クレジットカードブランドを表します。
typedef NS_ENUM(NSInteger, CYCardBrand) {
    /// \~
    /// Mastercard
    CYMasterCard,
    /// \~
    /// VISA
    CYVisa,
    /// \~english
    /// American Express
    /// \~japanese
    /// アメックス
    CYAMEX,
    /// \~english
    /// Japan Credit Bureau
    /// \~japanese
    /// JCB
    CYJCB,
    /// \~english
    /// Diners Club International
    /// \~japanese
    /// ダイナース
    CYDiners,
    /// \~english
    /// Unknown
    /// \~japanese
    /// 不明なブランド
    CYUnknownCardBrand
};

/// \~english
/// Converts a CYCurrency to its corresponding ISO currency code
/// \~japanese
/// `CYCurrency` に該当する ISO 通貨コードを返します。
static inline NSString *NSStringFromCYCurrency(CYCurrency const aCurrency)
{
    switch(aCurrency) {
        case CYCurrencyJPY: return @"JPY";
        default:            return nil;
    }
}

/// \~english
/// Converts an ISO currency code to a CYCurrency
/// \~japanese
/// ISO 通貨コードに該当する `CYCurrency` を返します。
static inline CYCurrency CYCurrencyFromString(NSString * const aCurrencyCode)
{
    NSString * const code = [aCurrencyCode lowercaseString];
    if([code isEqualToString:@"jpy"])
        return CYCurrencyJPY;
    else
        return CYCurrencyInvalid;
}

/// \~english
/// Converts a CYCardBrand to a string for display
/// \~japanese
/// 表示のため `CYCardBrand` を文字列に変換します。
static inline NSString *NSStringFromCYCardbrand(CYCardBrand const aCardBrand)
{
    switch(aCardBrand) {
        case CYVisa:       return @"Visa";
        case CYMasterCard: return @"MasterCard";
        case CYAMEX:       return @"AMEX";
        case CYJCB:        return @"JCB";
        case CYDiners:     return @"Diners";
        case CYUnknownCardBrand:
            return @"Unknown";
    }
}
