// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import "CYPrinter.h"

@interface CYPrinter (CYReceiptPrinting)

/// \~english
/// Prints a receipt using a connected printer.
/// \~japanese
/// 接続されたプリンタで、 `ReceiptML` 形式のレシートを印字します。
- (void)printReceiptML:(NSString *)aSource;
@end
