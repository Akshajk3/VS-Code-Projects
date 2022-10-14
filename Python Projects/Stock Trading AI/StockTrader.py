import alpaca_trade_api as tradeapi


class Martingale(object):
    def __init__(self):
        self.key = 'PKED2UQWYTF3V7J9BBY6'
        self.secret = 'Q6fGmao9NRlyp1VZzVguyoqgewUdtjHlonOe8Ofo'
        self.alpaca_endpoint = 'https://paper-api.alpaca.markets'
        self.api = tradeapi.REST(self.key, self.secret, self.alpaca_endpoint)
        self.symbol = 'IVV'
        self.current_order = None
        self.last_price = 1

        try:
            self.position = int(self.api.get_position(self.symbol).qty)
        except:
            self.position = 0
    
    def submit_order(self, target):
        if self.current_order is not None:
            self.api.cancel_order(self.current_order.id)
        
        delta = target - self.position
        if delta == 0:
            return
        print(f'Processing the order for {target} shares')

        if delta > 0:
            buy_quantity = delta
            if self.position < 0:
                buy_quantity = min(abs(self.position))
            print(f'Buying {buy_quantity} shares')
            self.current_order = self.api.submit_order(self.symbol, buy_quantity, 'buy', 'limit', 'day', self.last_price)
        elif delta < 0:
            sell_quantity = abs(delta)
            if self.position > 0:
                sell_quantity = min(abs(self.position), sell_quantity)
            print(f'Selling {sell_quantity} shares')
            self.current_order = self.api.submit_order(self.symbol, sell_quantity, 'sell', 'limit', 'day', self.last_price)

if __name__ == '__main__':
    t = Martingale()
    t.submit_order(3)