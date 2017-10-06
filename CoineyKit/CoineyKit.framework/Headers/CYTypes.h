// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <Foundation/Foundation.h>

/// \~english
/// Represents a payment method.
/// \~japanese
/// 決済方法を表します。
typedef NS_ENUM(int64_t, CYPaymentMethod) {
    CYPaymentMethodUnknown,
    CYPaymentMethodCreditCard,
    CYPaymentMethodWechatPay
};

/// \~english
/// Represents a set of payment methods.
/// \~japanese
/// 決済方法の集合を表します。
typedef NS_OPTIONS(int64_t, CYPaymentMethodMask) {
    CYPaymentMethodMaskCreditCard = 1 << CYPaymentMethodCreditCard,
    CYPaymentMethodMaskWechatPay  = 1 << CYPaymentMethodWechatPay
};

/// \~english
/// Represents a currency.
/// (Currently only Japanese Yen are supported)
/// \~japanese
/// 通貨を表します。
/// (現在日本円のみ対応)
typedef NS_ENUM(int64_t, CYCurrency) {
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
typedef NS_ENUM(int64_t, CYCardBrand) {
    /// \~english
    /// Unknown
    /// \~japanese
    /// 不明なブランド
    CYUnknownCardBrand,
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
    /// Discover
    /// \~japanese
    /// ディスカバー
    CYDiscover,
    /// \~english
    /// Saison
    /// \~japanese
    /// セゾン
    CYSaison
};

typedef NS_OPTIONS(int64_t, CYCardBrandMask) {
    CYCardBrandMaskMasterCard = 1 << CYMasterCard,
    CYCardBrandMaskVisa       = 1 << CYVisa,
    CYCardBrandMaskAMEX       = 1 << CYAMEX,
    CYCardBrandMaskJCB        = 1 << CYJCB,
    CYCardBrandMaskDiners     = 1 << CYDiners,
    CYCardBrandMaskDiscover   = 1 << CYDiscover,
    CYCardBrandMaskSaison     = 1 << CYSaison
};

typedef NS_ENUM(int64_t, CYFinancingType) {
    CYFinancingNone,
    CYFinancingRevolving,
    CYFinancing2Installments,
    CYFinancingBonus,
    CYFinancing3Installments,
    CYFinancing5Installments,
    CYFinancing6Installments,
    CYFinancing10Installments,
    CYFinancing12Installments,
    CYFinancing15Installments,
    CYFinancing18Installments,
    CYFinancing20Installments,
    CYFinancing24Installments
};

typedef NS_OPTIONS(int64_t, CYFinancingMask) {
    CYFinancingMaskRevolving      = 1 << CYFinancingRevolving,
    CYFinancingMask2Installments  = 1 << CYFinancing2Installments,
    CYFinancingMaskBonus          = 1 << CYFinancingBonus,
    CYFinancingMask3Installments  = 1 << CYFinancing3Installments,
    CYFinancingMask5Installments  = 1 << CYFinancing5Installments,
    CYFinancingMask6Installments  = 1 << CYFinancing6Installments,
    CYFinancingMask10Installments = 1 << CYFinancing10Installments,
    CYFinancingMask12Installments = 1 << CYFinancing12Installments,
    CYFinancingMask15Installments = 1 << CYFinancing15Installments,
    CYFinancingMask18Installments = 1 << CYFinancing18Installments,
    CYFinancingMask20Installments = 1 << CYFinancing20Installments,
    CYFinancingMask24Installments = 1 << CYFinancing24Installments
};

/// \~english
/// Converts a CYCurrency to its corresponding ISO currency code
/// \~japanese
/// `CYCurrency` に該当する ISO 通貨コードを返します。
static inline NSString * _Nullable NSStringFromCYCurrency(CYCurrency const aCurrency)
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
static inline CYCurrency CYCurrencyFromString(NSString * const _Nullable aCurrencyCode)
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
static inline NSString * _Nonnull NSStringFromCYCardbrand(CYCardBrand const aCardBrand)
{
    switch(aCardBrand) {
        case CYVisa:       return @"VISA";
        case CYMasterCard: return @"MasterCard";
        case CYAMEX:       return @"AMEX";
        case CYJCB:        return @"JCB";
        case CYDiners:     return @"Diners";
        case CYDiscover:   return @"Discover";
        case CYSaison:     return @"Saison";
        case CYUnknownCardBrand:
            return @"Unknown";
    }
}

