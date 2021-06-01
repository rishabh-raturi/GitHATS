TCanvas *c1[32];
const char*  mode[3] = {"jpsi", "psip", "rare"};
int n = 21;
double flag;

void plot(TH1D *hist_data, TH1D *hist_mc, const char* str1, const char* str, int i, double l_bound, double u_bound)
{

	c1[i] = new TCanvas("c1","c1", 500, 450);
	TPad *p1   = new TPad("p1","p1", 0.05, 0.25, 0.995, 0.97);
    	TPad *p2   = new TPad("p2","p2", 0.05, 0.02, 0.995, 0.24);
    	p1->Draw();
    	p2->Draw();

	p1->cd();
	//gPad->SetLogy();
	hist_data->SetStats(0);
	hist_mc->SetStats(0);

	hist_data->SetMarkerStyle(8);
	hist_data->SetMarkerColor(1);
	hist_mc->SetLineWidth(2);
	hist_mc->SetLineColor(46);
	hist_mc->SetFillColor(kRed-7);
	hist_mc->SetFillStyle(3008);

	
	hist_data->SetTitle(str);
	hist_data->GetXaxis()->SetTitle(str);
	hist_data->GetYaxis()->SetTitle("Entries");
	hist_data->GetYaxis()->SetTitleOffset(1.6);

	hist_data->Draw("e1");
	hist_mc->Draw("histsame");

	auto legend = new TLegend(0.85,0.85,0.95,0.95);
    	legend->AddEntry(hist_mc,"MC", "F");
    	legend->AddEntry(hist_data,"Data", "P");
    	legend->Draw();

	p2->cd();
	p2->SetBottomMargin(0.2);
	TH1D *h3 = (TH1D*)hist_mc->Clone("h3");
	h3->GetYaxis()->SetRangeUser(0.5,1.5);
	h3->SetTitle("");
	h3->GetYaxis()->SetTitle("");
	h3->GetXaxis()->SetTitle(str);
	h3->GetYaxis()->SetTitleSize( (0.7/0.3)*hist_mc->GetXaxis()->GetLabelSize() );
    	h3->GetXaxis()->SetTitleSize( (0.7/0.3)*hist_mc->GetXaxis()->GetLabelSize() );
    	h3->GetYaxis()->SetTitleOffset(0.5);
    	h3->GetYaxis()->SetLabelSize( (0.7/0.3)*hist_mc->GetXaxis()->GetLabelSize() );
    	h3->GetXaxis()->SetLabelSize( (0.7/0.3)*hist_mc->GetXaxis()->GetLabelSize() );
    	h3->GetYaxis()->SetNdivisions(505);
	h3->SetStats(0);
	h3->Divide(hist_data);
	h3->SetMarkerStyle(8);
    	h3->SetMarkerColor(1);
	h3->Draw("e1");

	double x[n];
	flag = l_bound;
	for(int i=0;i<n;i++)
	{
		x[i] = flag;
		flag = flag + (u_bound-l_bound)/20;
		//cout << "variable-> " << str1 << endl;
	}
	TGraph *grshade =  new TGraph(2*n);
	for(int i=0;i<n;i++)
	{
		grshade->SetPoint(i, x[i], 0.8);
		grshade->SetPoint(n+i, x[n-i-1], 1.2);
	}
	grshade->SetFillColor(kGreen);
	grshade->SetFillStyle(3008);
	grshade->Draw("f");

	c1[i]->SaveAs(Form("/eos/user/r/rraturi/www/cutopt/lept/2016/splot/%s.pdf", str1));
	c1[i]->SaveAs(Form("/eos/user/r/rraturi/www/cutopt/lept/2016/splot/%s.png", str1));
	
	//c1[i]->SaveAs(Form("/eos/user/r/rraturi/www/cutopt/Jan28/2018/blxy/splot/%s.pdf", str1));
        //c1[i]->SaveAs(Form("/eos/user/r/rraturi/www/cutopt/Jan28/2018/blxy/splot/%s.png", str1));

	//cout << "variable-> " << str1 << endl;
	delete c1[i];
}


void loop()
{

	gROOT->SetBatch(1);
	const char* file = "/eos/user/r/rraturi/cutopt/2016/tmva/newvar/red_ntuples"; 
	TChain *ch = new TChain("tree");
	ch->Add(Form("%s/JPsi_DataSet_with_sWeight.root", file));
	TTree *tr = ch;

	TChain *ch1 = new TChain("tree");
	ch1->Add(Form("%s/JPsi_MC_ForFit.root", file));
	TTree *tr1 = ch1;


	const char* var_name[32] = {"CosThetaK", "CosThetaL", "Phi", "BDT", "Npv", "BsIso", "Bpt", "Bphi", "Bvtxcl", "mumIso", "mupIso", "Blxysig", "Bcosalphabs2d", "Kppt", "Kmpt", "Mumpt", "Muppt", "Kmtrkdcasigbs", "Kptrkdcasigbs", "Mumdcasigbs", "Mupdcasigbs", "KmtrkMinIP", "KptrkMinIP", "MupMinIP", "MumMinIP", "kmtrkIso", "kptrkIso", "Kmeta", "Kpeta", "Mumeta", "Mupeta", "Beta"};

	const char* title[32] = {"cos#theta_{K}", "cos#theta_{L}", "#phi", "BDT", "Npv", "B_{s} Isolation", "B_{s} p_{T}", "B_{s} #phi", "B_{s} vtx. CL", "#mu^{-} Isolation", "#mu^{+} Isolation", "B_{s} L_{xy}/#sigma", "B_{s} cos#alpha_{xy}", "K^{+} p_{T}", "K^{-} p_{T}", "#mu^{-} p_{T}", "#mu^{+} p_{T}", "K^{-} trk. DCA/#sigma", "K^{+} trk. DCA/#sigma",  "#mu^{-} DCA/#sigma", "#mu^{+} DCA/#sigma", "K^{-} trk. MinIP", "K^{+} trk. MinIP", "#mu^{+} MinIP", "#mu^{-} MinIP", "K^{-} trk. Isolation", "K^{+} trk. Isolation", "K^{-} #eta", "K^{+} #eta", "#mu^{-} #eta", "#mu^{+} #eta", "B_{s} #eta"};

	double l_bound[32] = {-1., -1., -3.5, -0.1, 0., 0.2, 10., -3., 0., 0.2, 0.2, 10., 0.9999, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.2 , 0.2, -3.0, -3.0, -2.5, -2.5, -2.5};
	double u_bound[32] = {1., +1., 3.5, 0.40, 50., 1.1, 40., 3., 1., 1.1, 1.1, 50., 1.0, 10., 10., 30., 30., 20., 20., 20., 20., 0.2, 0.2, 0.2, 0.2, 1.1, 1.1, 3.0, 3.0, 2.5, 2.5, 2.5};

	TH1D* h_data; //histogram pointer
	TH1D* h_mc;
	int n = 50; // number of bins
	double sc1, sc2;
	double norm = 1; 
	//loop for jpsi Unfiltered MC
	for(int i=0;i<32;i++)
	{
	  	h_data = new TH1D("h_data", "", n, l_bound[i], u_bound[i]);	
		h_mc   = new TH1D("h_mc", "", n, l_bound[i], u_bound[i]);
		tr->Project("h_data", var_name[i], "s_wt");
		tr1->Project("h_mc", var_name[i], "Puw8");

		// unit area normalization
		sc1 = norm/h_data->Integral();
		h_data->Scale(sc1);
		sc2 = norm/h_mc->Integral();
		h_mc->Scale(sc2);

		plot(h_data, h_mc, var_name[i], title[i], i, l_bound[i], u_bound[i] );
		delete h_data;
		delete h_mc;
		sc1=0;
		sc2=0;
	}

}

