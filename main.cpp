#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Agent.h"
#include "GlobalTrendAnalyzer.h"
#include "Price.h"
#include "PriceDataProvider.h"

int main() {
  PriceDataProvider dp;
  GlobalTrendAnalyzer globalTrendAnalyzer;

  std::string testCase = "StopLoss/final1point5Loss25/final";
  double delta = 0.015;
  double loss = 0.25;
  double unit = 62.26;
  double cash = 10000;

  Agent agentBTCLong =
      Agent(1, delta, unit, loss,
            "../rez/BTC/" + testCase + "/BTCUSDTLongSellLog.csv",
            "../rez/BTC/" + testCase + "/BTCUSDTLongBuyLog.csv");
  Agent agentBTCShort =
      Agent(-1, delta, unit, loss,
            "../rez/BTC/" + testCase + "/BTCUSDTShortSellLog.csv",
            "../rez/BTC/" + testCase + "/BTCUSDTShortBuyLog.csv");
  std::vector<Price> priceListBTC =
      dp.getPrices("../data/BTCUSDT.csv", "BTCUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("BTCUSDT",
                              "../rez/BTC/" + testCase + "/BTCUSDTADXLog.csv");
  double BTCCashAvailable = cash;
  std::string BTCValueLog = "../rez/BTC/" + testCase + "/BTCValueLog.csv";

  Agent agentETHLong =
      Agent(1, delta, unit, loss,
            "../rez/ETH/" + testCase + "/ETHUSDTLongSellLog.csv",
            "../rez/ETH/" + testCase + "/ETHUSDTLongBuyLog.csv");
  Agent agentETHShort =
      Agent(-1, delta, unit, loss,
            "../rez/ETH/" + testCase + "/ETHUSDTShortSellLog.csv",
            "../rez/ETH/" + testCase + "/ETHUSDTShortBuyLog.csv");
  std::vector<Price> priceListETH =
      dp.getPrices("../data/ETHUSDT.csv", "ETHUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("ETHUSDT",
                              "../rez/ETH/" + testCase + "/ETHUSDTADXLog.csv");
  double ETHCashAvailable = cash;
  std::string ETHValueLog = "../rez/ETH/" + testCase + "/ETHValueLog.csv";

  Agent agentSOLLong =
      Agent(1, delta, unit, loss,
            "../rez/SOL/" + testCase + "/SOLUSDTLongSellLog.csv",
            "../rez/SOL/" + testCase + "/SOLUSDTLongBuyLog.csv");
  Agent agentSOLShort =
      Agent(-1, delta, unit, loss,
            "../rez/SOL/" + testCase + "/SOLUSDTShortSellLog.csv",
            "../rez/SOL/" + testCase + "/SOLUSDTShortBuyLog.csv");
  std::vector<Price> priceListSOL =
      dp.getPrices("../data/SOLUSDT.csv", "SOLUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("SOLUSDT",
                              "../rez/SOL/" + testCase + "/SOLUSDTADXLog.csv");
  double SOLCashAvailable = cash;
  std::string SOLValueLog = "../rez/SOL/" + testCase + "/SOLValueLog.csv";

  Agent agentXRPLong =
      Agent(1, delta, unit, loss,
            "../rez/XRP/" + testCase + "/XRPUSDTLongSellLog.csv",
            "../rez/XRP/" + testCase + "/XRPUSDTLongBuyLog.csv");
  Agent agentXRPShort =
      Agent(-1, delta, unit, loss,
            "../rez/XRP/" + testCase + "/XRPUSDTShortSellLog.csv",
            "../rez/XRP/" + testCase + "/XRPUSDTShortBuyLog.csv");
  std::vector<Price> priceListXRP =
      dp.getPrices("../data/XRPUSDT.csv", "XRPUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("XRPUSDT",
                              "../rez/XRP/" + testCase + "/XRPUSDTADXLog.csv");
  double XRPCashAvailable = cash;
  std::string XRPValueLog = "../rez/XRP/" + testCase + "/XRPValueLog.csv";

  Agent agentADALong =
      Agent(1, delta, unit, loss,
            "../rez/ADA/" + testCase + "/ADAUSDTLongSellLog.csv",
            "../rez/ADA/" + testCase + "/ADAUSDTLongBuyLog.csv");
  Agent agentADAShort =
      Agent(-1, delta, unit, loss,
            "../rez/ADA/" + testCase + "/ADAUSDTShortSellLog.csv",
            "../rez/ADA/" + testCase + "/ADAUSDTShortBuyLog.csv");
  std::vector<Price> priceListADA =
      dp.getPrices("../data/ADAUSDT.csv", "ADAUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("ADAUSDT",
                              "../rez/ADA/" + testCase + "/ADAUSDTADXLog.csv");
  double ADACashAvailable = cash;
  std::string ADAValueLog = "../rez/ADA/" + testCase + "/ADAValueLog.csv";

  Agent agentBNBLong =
      Agent(1, delta, unit, loss,
            "../rez/BNB/" + testCase + "/BNBUSDTLongSellLog.csv",
            "../rez/BNB/" + testCase + "/BNBUSDTLongBuyLog.csv");
  Agent agentBNBShort =
      Agent(-1, delta, unit, loss,
            "../rez/BNB/" + testCase + "/BNBUSDTShortSellLog.csv",
            "../rez/BNB/" + testCase + "/BNBUSDTShortBuyLog.csv");
  std::vector<Price> priceListBNB =
      dp.getPrices("../data/BNBUSDT.csv", "BNBUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("BNBUSDT",
                              "../rez/BNB/" + testCase + "/BNBUSDTADXLog.csv");
  double BNBCashAvailable = cash;
  std::string BNBValueLog = "../rez/BNB/" + testCase + "/BNBValueLog.csv";

  Agent agentDOGELong =
      Agent(1, delta, unit, loss,
            "../rez/DOGE/" + testCase + "/DOGEUSDTLongSellLog.csv",
            "../rez/DOGE/" + testCase + "/DOGEUSDTLongBuyLog.csv");
  Agent agentDOGEShort =
      Agent(-1, delta, unit, loss,
            "../rez/DOGE/" + testCase + "/DOGEUSDTShortSellLog.csv",
            "../rez/DOGE/" + testCase + "/DOGEUSDTShortBuyLog.csv");
  std::vector<Price> priceListDOGE =
      dp.getPrices("../data/DOGEUSDT.csv", "DOGEUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair(
      "DOGEUSDT", "../rez/DOGE/" + testCase + "/DOGEUSDTADXLog.csv");
  double DOGECashAvailable = cash;
  std::string DOGEValueLog = "../rez/DOGE/" + testCase + "/DOGEValueLog.csv";

  Agent agentAVAXLong =
      Agent(1, delta, unit, loss,
            "../rez/AVAX/" + testCase + "/AVAXUSDTLongSellLog.csv",
            "../rez/AVAX/" + testCase + "/AVAXUSDTLongBuyLog.csv");
  Agent agentAVAXShort =
      Agent(-1, delta, unit, loss,
            "../rez/AVAX/" + testCase + "/AVAXUSDTShortSellLog.csv",
            "../rez/AVAX/" + testCase + "/AVAXUSDTShortBuyLog.csv");
  std::vector<Price> priceListAVAX =
      dp.getPrices("../data/AVAXUSDT.csv", "AVAXUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair(
      "AVAXUSDT", "../rez/AVAX/" + testCase + "/AVAXUSDTADXLog.csv");
  double AVAXCashAvailable = cash;
  std::string AVAXValueLog = "../rez/AVAX/" + testCase + "/AVAXValueLog.csv";

  double globalFraction = 1.0;

  std::fstream fout;

  for (int i = 0; i < priceListBTC.size(); ++i) {
    // BTC
    globalTrendAnalyzer.addPrice("BTCUSDT", priceListBTC [ i ]);
    BTCCashAvailable =
        agentBTCLong.run(priceListBTC [ i ], globalFraction, BTCCashAvailable);
    BTCCashAvailable =
        agentBTCShort.run(priceListBTC [ i ], globalFraction, BTCCashAvailable);
    fout.open(BTCValueLog, std::ios::out | std::ios::app);
    fout << priceListBTC [ i ].time << "," << BTCCashAvailable << ","
         << agentBTCLong.getInventoryValue(priceListBTC [ i ]) << ","
         << agentBTCShort.getInventoryValue(priceListBTC [ i ]) << "\r\n";
    fout.close();

    // ETH
    if (i < priceListETH.size()) {
      globalTrendAnalyzer.addPrice("ETHUSDT", priceListETH [ i ]);
      ETHCashAvailable = agentETHLong.run(priceListETH [ i ], globalFraction,
                                          ETHCashAvailable);
      ETHCashAvailable = agentETHShort.run(priceListETH [ i ], globalFraction,
                                           ETHCashAvailable);
      fout.open(ETHValueLog, std::ios::out | std::ios::app);
      fout << priceListETH [ i ].time << "," << ETHCashAvailable << ","
           << agentETHLong.getInventoryValue(priceListETH [ i ]) << ","
           << agentETHShort.getInventoryValue(priceListETH [ i ]) << "\r\n";
      fout.close();
    }

    // SOL
    if (i < priceListSOL.size()) {
      globalTrendAnalyzer.addPrice("SOLUSDT", priceListSOL [ i ]);
      SOLCashAvailable = agentSOLLong.run(priceListSOL [ i ], globalFraction,
                                          SOLCashAvailable);
      SOLCashAvailable = agentSOLShort.run(priceListSOL [ i ], globalFraction,
                                           SOLCashAvailable);
      fout.open(SOLValueLog, std::ios::out | std::ios::app);
      fout << priceListSOL [ i ].time << "," << SOLCashAvailable << ","
           << agentSOLLong.getInventoryValue(priceListSOL [ i ]) << ","
           << agentSOLShort.getInventoryValue(priceListSOL [ i ]) << "\r\n";
      fout.close();
    }

    // XRP
    if (i < priceListXRP.size()) {
      globalTrendAnalyzer.addPrice("XRPUSDT", priceListXRP [ i ]);
      XRPCashAvailable = agentXRPLong.run(priceListXRP [ i ], globalFraction,
                                          XRPCashAvailable);
      XRPCashAvailable = agentXRPShort.run(priceListXRP [ i ], globalFraction,
                                           XRPCashAvailable);
      fout.open(XRPValueLog, std::ios::out | std::ios::app);
      fout << priceListXRP [ i ].time << "," << XRPCashAvailable << ","
           << agentXRPLong.getInventoryValue(priceListXRP [ i ]) << ","
           << agentXRPShort.getInventoryValue(priceListXRP [ i ]) << "\r\n";
      fout.close();
    }

    // ADA
    if (i < priceListADA.size()) {
      globalTrendAnalyzer.addPrice("ADAUSDT", priceListADA [ i ]);
      ADACashAvailable = agentADALong.run(priceListADA [ i ], globalFraction,
                                          ADACashAvailable);
      ADACashAvailable = agentADAShort.run(priceListADA [ i ], globalFraction,
                                           ADACashAvailable);
      fout.open(ADAValueLog, std::ios::out | std::ios::app);
      fout << priceListADA [ i ].time << "," << ADACashAvailable << ","
           << agentADALong.getInventoryValue(priceListADA [ i ]) << ","
           << agentADAShort.getInventoryValue(priceListADA [ i ]) << "\r\n";
      fout.close();
    }

    // BNB
    if (i < priceListBNB.size()) {
      globalTrendAnalyzer.addPrice("BNBUSDT", priceListBNB [ i ]);
      BNBCashAvailable = agentBNBLong.run(priceListBNB [ i ], globalFraction,
                                          BNBCashAvailable);
      BNBCashAvailable = agentBNBShort.run(priceListBNB [ i ], globalFraction,
                                           BNBCashAvailable);
      fout.open(BNBValueLog, std::ios::out | std::ios::app);
      fout << priceListBNB [ i ].time << "," << BNBCashAvailable << ","
           << agentBNBLong.getInventoryValue(priceListBNB [ i ]) << ","
           << agentBNBShort.getInventoryValue(priceListBNB [ i ]) << "\r\n";
      fout.close();
    }

    // DOGE
    if (i < priceListDOGE.size()) {
      globalTrendAnalyzer.addPrice("DOGEUSDT", priceListDOGE [ i ]);
      DOGECashAvailable = agentDOGELong.run(priceListDOGE [ i ], globalFraction,
                                            DOGECashAvailable);
      DOGECashAvailable = agentDOGEShort.run(priceListDOGE [ i ],
                                             globalFraction, DOGECashAvailable);
      fout.open(DOGEValueLog, std::ios::out | std::ios::app);
      fout << priceListDOGE [ i ].time << "," << DOGECashAvailable << ","
           << agentDOGELong.getInventoryValue(priceListDOGE [ i ]) << ","
           << agentDOGEShort.getInventoryValue(priceListDOGE [ i ]) << "\r\n";
      fout.close();
    }

    // AVAX
    if (i < priceListAVAX.size()) {
      globalTrendAnalyzer.addPrice("AVAXUSDT", priceListAVAX [ i ]);
      AVAXCashAvailable = agentAVAXLong.run(priceListAVAX [ i ], globalFraction,
                                            AVAXCashAvailable);
      AVAXCashAvailable = agentAVAXShort.run(priceListAVAX [ i ],
                                             globalFraction, AVAXCashAvailable);
      fout.open(AVAXValueLog, std::ios::out | std::ios::app);
      fout << priceListAVAX [ i ].time << "," << AVAXCashAvailable << ","
           << agentAVAXLong.getInventoryValue(priceListAVAX [ i ]) << ","
           << agentAVAXShort.getInventoryValue(priceListAVAX [ i ]) << "\r\n";
      fout.close();
    }

    globalFraction = globalTrendAnalyzer.getBuyFraction();
    //    std::cout << "Buy fraction: " << globalFraction << std::endl;
  }

  return 0;
}
