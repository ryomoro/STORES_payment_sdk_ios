// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

/// \~english
/// Represents a currency.
/// (Currently only Japanese Yen are supported)
typedef enum {
    /// \~english
    /// Japanese Yen
    CYCurrencyJPY
} CYCurrency;

/// \~english
/// Represents a brand of credit card.
typedef enum {
    /// \~english
    /// Mastercard
    CYMasterCard,
    /// \~english
    /// VISA
    CYVisa,
    /// \~english
    /// American Express
    CYAMEX,
    /// \~english
    /// Japan Credit Bureau
    CYJCB,
    /// \~english
    /// Diners Club International
    CYDiners,
    /// \~english
    /// Unknown
    CYUnknownCardBrand
} CYCardBrand;