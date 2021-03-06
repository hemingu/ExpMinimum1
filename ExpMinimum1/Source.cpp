#include "Common.h"

#include "ADCInfo.h"
#include "Const.h"


using namespace Constants;



int main(int argc, char *argv[])
{
    // Open ROOT window
    TApplication app("Root Window", &argc, argv);


    // file input (Files in same location as Source.cpp)
    // (Y:\Documents\Visual Studio 2017\Projects\ConsoleApplication1\ConsoleApplication1)
    TFile *fileCo = new TFile("AH2017Jun07_120130.root", "read");
    TFile *fileCs = new TFile("AH2017Jun07_121525.root", "read");
    TFile *fileBa = new TFile("AH2017Jun07_122129.root", "read");
    TFile *fileBG = new TFile("AH2017Jun07_122616.root", "read");
    //TFile *fileHist = new TFile("histgrams.root", "read");

    TCanvas *canvases[NCANVAS];
    

    // Make Co60 Class
    ADCInfo infoCo(fileCo, Element::Co);
    TH1D *histCo = new TH1D("ADC Co60", Constants::AXIS_NAME, Constants::BIN, Constants::HISTMIN, Constants::HISTMAX);
    for (Int_t i = 0; i < infoCo.nEntries; i++)
    {
        histCo->Fill((Double_t)infoCo.ADCChannel[i]);
    }
    canvases[0] = new TCanvas();
    //TCanvas *c1 = new TCanvas();
    histCo->Draw();

    // Cs137
    ADCInfo infoCs(fileCs, Element::Cs);
    TH1D *histCs = new TH1D("ADC Cs137", Constants::AXIS_NAME, Constants::BIN, Constants::HISTMIN, Constants::HISTMAX);
    for (Int_t i = 0; i < infoCs.nEntries; i++)
    {
        histCs->Fill((Double_t)infoCs.ADCChannel[i]);
    }
    canvases[1] = new TCanvas();
    //TCanvas *c2 = new TCanvas();
    histCs->Draw();

    // Ba133
    ADCInfo infoBa(fileBa, Element::Ba);
    TH1D *histBa = new TH1D("ADC Ba133", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    for (Int_t i = 0; i < infoBa.nEntries; i++)
    {
        histBa->Fill((Double_t)infoBa.ADCChannel[i]);
    }
    canvases[2] = new TCanvas();
    //TCanvas *c3 = new TCanvas();
    histBa->Draw();

    // BackGround
    ADCInfo infoBG(fileBG, Element::BG);
    TH1D *histBG = new TH1D("ADC BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    for (Int_t i = 0; i < infoBG.nEntries; i++)
    {
        histBG->Fill((Double_t)infoBG.ADCChannel[i]);
    }
    canvases[3] = new TCanvas();
    //TCanvas *c4 = new TCanvas();
    histBG->Draw();

    // Co - BG
    TH1D *histCoBG = new TH1D("ADC Co60 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    histCoBG->Add(histCo, histBG, 1.0, -(Double_t)infoCo.measurementTime / (Double_t)infoBG.measurementTime);
    canvases[4] = new TCanvas();
    //TCanvas *c5 = new TCanvas();
    histCoBG->Draw();

    // Cs - BG
    TH1D *histCsBG = new TH1D("ADC Cs137 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    histCsBG->Add(histCs, histBG, 1.0, -(Double_t)infoCs.measurementTime / (Double_t)infoBG.measurementTime);
    canvases[5] = new TCanvas();
    //TCanvas *c6 = new TCanvas();
    histCsBG->Draw();


    // Ba - BG
    TH1D *histBaBG = new TH1D("ADC Ba133 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    histBaBG->Add(histBa, histBG, 1.0, -(Double_t)infoBa.measurementTime / (Double_t)infoBG.measurementTime);
    canvases[6] = new TCanvas();
    //TCanvas *c7 = new TCanvas();
    histBaBG->Draw();



    for (Int_t i = 0; i < NCANVAS; i++)
    {
        canvases[i]->Update();
    }

    canvases[0]->Print("hist.pdf(");
    for (Int_t i = 1; i < NCANVAS-1; i++)
    {
        canvases[i]->Print("hist.pdf");
    }
    canvases[NCANVAS - 1]->Print("hist.pdf)");

    TFile hists("histograms.root", "RECREATE");
    histCo->Write();
    histCs->Write();
    histBa->Write();
    histBG->Write();
    histCoBG->Write();
    histCsBG->Write();
    histBaBG->Write();
    hists.Close();


    TNtuple *ntuple = new TNtuple("name", "title", "Co;Cs;Ba;BG");
    for (Int_t i = 0; i < infoBG.nEntries; i++)
    {

    }

    // Fitting histograms
    histCoBG->Fit("gaus");

    //app.Run();
    

    return 0;

}