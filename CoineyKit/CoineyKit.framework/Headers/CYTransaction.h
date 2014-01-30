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
@protocol CYTransaction <NSObject>

/// \~english
/// A unique transaction identifier
/// \~japanese
/// 決済の一意なID
@property(nonatomic, readonly) NSString *identifier;
/// \~english
/// A representation of the identifier for displaying to users.
/// (Not guaranteed to be unique)
/// \~japanese
/// ユーザーに表示するためにフォーマットされた決済ID
/// (一意であるとは限りません)
@property(nonatomic, readonly) NSString *humanReadableIdentifier;
/// \~english
/// Returns the date/time of the transaction
/// \~japanese
/// 決済の日時
@property(nonatomic, readonly) NSDate *chargeDate;
/// \~english
/// The currency of the transaction amount
/// \~japanese
/// 決済の通貨
@property(nonatomic, readonly) CYCurrency currency;
/// \~english
/// The amount of the transaction in its currency
/// \~japanese
/// 決済額
@property(nonatomic, readonly) NSNumber *amount;
/// \~english
/// The brand of credit card used to make the transaction
/// \~japanese
/// 決済に使われたカードブランド
@property(nonatomic, readonly) CYCardBrand cardBrand;
/// \~english
/// Returns a string containing the last 4 digits of the credit card's number
/// \~japanese
/// カード番号の下4桁
@property(nonatomic, readonly) NSString *cardSuffix;
/// \~english
/// Returns whether or not the transaction has been refunded
/// \~japanese
/// 返金済みかどうか
@property(nonatomic, readonly) BOOL isRefunded;
/// \~english
/// Returns the approval code from the acquirer
/// \~japanese
/// アクワイアラが発行する承認コード
@property(nonatomic, strong) NSString *approvalCode;

/// \~english
/// Generates a bitmap for the transaction's receipt.
/// \~japanese
/// 決済のレシートをビットマップとして描画します。
/// \param aWidth
///   \~english The width of the `UIImage` to be returned
///   \~japanese 生成する `UIImage` の幅
- (UIImage *)imageRepresentationWithWidth:(float const)aWidth;
    
/// \~english
/// Generates a ReceiptML string with the transaction data.
/// \~japanese
/// 決済データを ReceiptML 形式で返します。
- (NSString *)receiptMLRepresentation;
@end

typedef void (^CYTransactionLookupBlock)(id<CYTransaction> aTransaction, NSError *aError);

/// \~english
/// Queries Coiney for a given transaction identifier and if found, passes it to the completion block.
/// If none is found nil is passed for the transaction.
/// \~japanese
/// 渡したIDを元に決済を参照し、ブロックを実行します。
/// 一致するものあれば `CYTransaction` オブジェクトを、なければ `nil` をブロックに渡します。
/// \param aIdentifier
///   \~english The identifier of the transaction to look up
///   \~japanese 参照する決済ID
/// \param aCompletionBlock
///   \~english A block to be executed upon completion
///   \~japanese 参照後に実行するブロック
void CYLookUpTransaction(NSString *aIdentifier, CYTransactionLookupBlock aCompletionBlock);
