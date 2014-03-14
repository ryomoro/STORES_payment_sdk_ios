// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

// Implements support for ESC/POS based bluetooth printers
@import Foundation;

NSString * const kCYPrinterConnectedNotification,
         * const kCYPrinterDisconnectedNotification,
         * const kCYPrinterBeganPrintingNotification,
         * const kCYPrinterEndedPrintingNotification;

/// \~english
/// Receipt printer interface
/// \~japanese
/// レシートプリンタ用インタフェース
@interface CYPrinter : NSObject
@property(readonly, getter=isConnected) BOOL connected;


/// \~english
/// Paper width in pixels
/// \~japanese
/// ピクセル数で表した用紙幅
@property(readonly) NSInteger bitmapWidth;

/// \~english
/// Paper width in characters
/// \~japanese
/// 文字数で表した用紙幅
@property(readonly) NSInteger lineLength;

/// \~english
/// Name of printer for displaying to user
/// \~japanese
/// ユーザー表示用のプリンタ名称
@property(readonly) NSString *displayName;

/// \~english
/// Whether printing is enabled in CoineyKit. Default is off.
/// \~japanese
/// `CoineyKit` でレシート印刷がオンかどうか。デフォルトはオフ。
+ (BOOL)isPrintingEnabled;

/// \~english
/// Enables or disables receipt printing. Usually called once after app launch.
/// \~japanese
/// レシート印刷機能のオン・オフを切り替えます。通常はローンチ時に一回呼びます。
+ (void)setPrintingEnabled:(BOOL)aFlag;

/// \~english
/// Returns a list of connected printers.
/// \~japanese
/// 接続済みのプリンタ一覧を返します。
+ (NSArray *)connectedPrinters;

/// \~english
/// Whether bitmap printing is impractical, due to its speed or other considerations. (This does *not* mean that it is unsupported)
/// \~japanese
/// 印字スピード等の理由で、ビットマップモードでの印字が現実的でない場合は、YESを返します。(サポート対象外というわけではありません)
+ (BOOL)bitmapPrintingIsImpractical;

+ (instancetype)new  __attribute__((unavailable("+new not available; use +connectedPrinters")));
- (id)init           __attribute__((unavailable("-init not available; use +connectedPrinters")));

/// \~english
/// Executes a collection of print instructions
/// \param aBlock A block containing print instructions
/// \param aCut Whether to cut automatically when done.  For models without an automatic cutter,
/// feeds to the manual cutting head.
/// \~japanese
/// 複数の印字命令をバッチで実行します。
/// \param aBlock プリンタに送る印字命令
/// \param aCut 印字後、オートカッターを作動させるかどうか。オートカッター非搭載のプリンタでは、手動カッターの
/// 位置まで用紙送りします
- (void)batchPrint:(dispatch_block_t)aBlock cutWhenDone:(BOOL)aCut;

/// \~english
/// Prints a string. Wraps as necessary.
/// \~japanese
/// 文字列をプリントします。一行に収まらない場合は、2行目にラップします。
- (void)printText:(NSString *)aText;

/// \~english
/// Prints an image.
/// \~japanese
/// `UIImage` をプリントします。
- (void)printImage:(UIImage *)aImage;
@end
