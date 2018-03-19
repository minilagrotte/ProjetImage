// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"
#include <time.h>

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

/*
************MyPanel**************************
*/

class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent );
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void OnSaveFile(wxString fileName);
    void OnMirror(int id);
    void OnBlur(int id);
    void OnRotate();
    void OnNegatif();
    void OnDesaturate();
    void OnSeuil();
    void OnMirrorMain(int id);
    void OnRotate90Main();
    void OnPosterize();
    void OnHistogramme();

    bool isImage();
private :
    MyImage *m_image = nullptr;		// used to load and process the image
    wxBitmap m_bitmap ;	// used to display the image
};

/*
************MyFrame**************************
*/
class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnSuperbe(wxCommandEvent& event);
	void OnResize(wxCommandEvent& event);
    void OnMouse(wxMouseEvent& event);
    void OnOpenImage(wxCommandEvent& event);
    void OnOpenImageDefault(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnProcess(wxCommandEvent& event);

    MyPanel* m_panel;
    clock_t t;
};

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_Hello = 1,
	ID_Truc,	// ID_Truc a pour valeur 2
	ID_Plus_Large,
	ID_Moins_large,	// ID_Machin a pour valeur 3
	ID_Open,
	ID_OpenDefault,
	ID_Save,
	ID_Mirror_hor,
	ID_Mirror_ver,
	ID_Blur,
	ID_Anti_Blur,
	ID_Rotate,
	ID_Negatif,
	ID_Desaturate,
	ID_Seuil,
	ID_Mirror_hor_main,
	ID_Mirror_ver_main,
	ID_Rotate90Main,
	ID_Posterize,
	ID_Histogramme

};

/*
************MyApp Function**************************
*/
IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( wxT("Hello World"), wxPoint(50, 50), wxSize(450, 340) );
	wxInitAllImageHandlers();
	frame->Show(true);
	return true;
}
/********************************************************************************************************
*
*
*
*               fonction sur Frame
*
*
*
**********************************************************************************************************/

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_panel = new MyPanel(this);

    Center();
    //---------------------------------------------------------------------------------------------------
	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(ID_Truc, wxT("Je suis ...\tShift-J")) ;
	Bind(wxEVT_MENU, &MyFrame::OnSuperbe, this, ID_Truc) ;

	menuFile->Append(ID_Plus_Large, wxT("Plus large\tCtrl-+")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_Plus_Large) ;

	menuFile->Append(ID_Moins_large, wxT("Moins Large\tCtrl--")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_Moins_large) ;

	menuFile->Append(ID_Open, wxT("Open image ...\tCtrl-o")) ;
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_Open) ;

	menuFile->Append(ID_OpenDefault, wxT("Open default image ...\tALT-o")) ;
	Bind(wxEVT_MENU, &MyFrame::OnOpenImageDefault, this, ID_OpenDefault) ;

	menuFile->Append(ID_Save, wxT("Save image ...\tCtrl-s")) ;
	Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save) ;

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;
    //---------------------------------------------------------------------------------------------------

	Bind(wxEVT_MOTION, &MyFrame::OnMouse,this);
    //---------------------------------------------------------------------------------------------------


	wxMenu *menuProcess = new wxMenu ;

	menuProcess->Append(ID_Mirror_hor, wxT("Effet miroir horizontal\tCtrl-m"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Mirror_hor);

	menuProcess->Append(ID_Mirror_ver, wxT("Effet miroir vertical\tCtrl-Shift-m"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Mirror_ver);

	menuProcess->Append(ID_Blur, wxT("Effet Blur\tCtrl-b"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Blur);

	menuProcess->Append(ID_Anti_Blur, wxT("Effet Antiblur\tCtrl-Shift-b"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Anti_Blur);

	menuProcess->Append(ID_Rotate, wxT("Effet rotation +90°\tCtrl-r"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Rotate);

    menuProcess->Append(ID_Negatif, wxT("Effet negatif\tAlt-n"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Negatif);

	menuProcess->Append(ID_Desaturate, wxT("désaturation\tAlt-d"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Desaturate);

	menuProcess->Append(ID_Seuil, wxT("Seuillage\tAlt-s"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Seuil);

	menuProcess->Append(ID_Mirror_hor_main, wxT("Mirroir horizontal fait main\tAlt-m"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Mirror_hor_main);

	menuProcess->Append(ID_Mirror_ver_main, wxT("Mirroir vertical fait main\tAlt-Shift-m"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Mirror_ver_main);

	menuProcess->Append(ID_Rotate90Main, wxT("Rotation 90 fait main\tAlt-r"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Rotate90Main);

	menuProcess->Append(ID_Posterize, wxT("Faire un posterize\tAlt-k"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Posterize);

	menuProcess->Append(ID_Histogramme, wxT("Faire un histogramme\tAlt-h"));
	Bind(wxEVT_MENU,&MyFrame::OnProcess, this, ID_Histogramme);



    //---------------------------------------------------------------------------------------------------

	wxMenu *menuHelp = new wxMenu ;

	menuHelp->Append(ID_Truc, wxT("En construction ...")) ;
    //---------------------------------------------------------------------------------------------------


	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append(menuFile, wxT("File" )) ;
	menuBar->Append(menuProcess, wxT("Process" )) ;
	menuBar->Append(menuHelp, wxT("Help"));
	SetMenuBar(menuBar) ;



	//wxStatusBar *stat = new wxStatusBar();
	//stat->SetStatusText(wxT("une belle bar de statut"));
	//this->SetStatusBar(stat);

	CreateStatusBar();





}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(wxT("Hello world from wxWidgets!"));

}

void MyFrame::OnSuperbe(wxCommandEvent& event)
{
	wxLogMessage(wxT("Je suis superbe"));
}

void MyFrame::OnResize(wxCommandEvent& event)
{
    wxSize size = GetSize();
    int delta;
    if(event.GetId() == ID_Moins_large){
        delta = -100;    }
    if(event.GetId() == ID_Plus_Large){
        delta = 100;    }

    if(size.GetWidth() > 0){
        size.SetWidth(size.GetWidth() + delta);
    }
    if(size.GetHeight() > 0){
        size.SetHeight(size.GetHeight()+ delta);
    }
    this->SetSize(size);
}

void MyFrame::OnMouse(wxMouseEvent& event){
    //wxEVT_MOTION
    wxPoint coord = event.GetPosition();
    //char str[100] = coord;
    wxString s;
    s.sprintf("x : %d / y : %d",coord.x, coord.y);
    SetStatusText(s);
}

void MyFrame::OnOpenImage(wxCommandEvent& event){
    wxString path = wxFileSelector(wxT("choisir une image"));
    SetStatusText(path);
    if(!path.empty()){
        m_panel->OpenImage(path);
    }
}

void MyFrame::OnOpenImageDefault(wxCommandEvent& event){
    m_panel->OpenImage(wxT("/users/info/etu-s4/rueth/M4105C/tp4/default.jpg"));
}

void MyFrame::OnSave(wxCommandEvent& event)
{
	//wxLogMessage(wxT("Je suis sauvegarde"));
	wxString path = wxSaveFileSelector("image","jpeg");
	path += wxT(".jpeg");
    if(!path.empty()){
        this->m_panel->OnSaveFile(path);
    }
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnProcess(wxCommandEvent& event){
    if(m_panel->isImage()){

        switch (event.GetId()){
        case ID_Mirror_hor:
            m_panel->OnMirror(ID_Mirror_hor);
            break;
        case ID_Mirror_ver:
            m_panel->OnMirror(ID_Mirror_ver);
            break;
        case ID_Blur:
            m_panel->OnBlur(ID_Blur);
            break;
        case ID_Anti_Blur:
            m_panel->OnBlur(ID_Anti_Blur);
            break;
        case ID_Rotate:
            m_panel->OnRotate();
            break;
        case ID_Negatif:
            //t = clock();
            m_panel->OnNegatif();
            //t = clock() - t;
            /*wxString s;
            s.sprintf("%d",t);
            SetStatusText(s);*/
            break;
        case ID_Desaturate:
            m_panel->OnDesaturate();
            break;
        case ID_Seuil:
            m_panel->OnSeuil();
            break;
        case ID_Mirror_hor_main:
            m_panel->OnMirrorMain(ID_Mirror_hor_main);
            break;
        case ID_Mirror_ver_main:
            m_panel->OnMirrorMain(ID_Mirror_ver_main);
            break;
        case ID_Rotate90Main:
            m_panel->OnRotate90Main();
            break;
        case ID_Posterize:
            m_panel->OnPosterize();
            break;
        case ID_Histogramme:
            m_panel->OnHistogramme();
            break;

        }
    }
}

/*************************************************************************************************
*
*
*
******* Méthode sur Panel
*******
*
*
*
**************************************************************************************************/

MyPanel::MyPanel(wxWindow *parent)
: wxPanel(parent) {
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
}


MyPanel::~MyPanel() {
}

void MyPanel::OpenImage(wxString path){
    if(m_image != nullptr){
        m_image->Destroy();
    }
    m_image = new MyImage(path);
    wxSize size = m_image->GetSize();
    this->GetParent()->SetClientSize(size);
    Refresh();
}

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    if(m_image != nullptr){
        m_bitmap = wxBitmap(*m_image);
        wxPaintDC dc(this);
        dc.DrawBitmap(m_bitmap,0,0);
    }
}

void MyPanel::OnSaveFile(wxString fileName){
    m_bitmap.SaveFile(fileName,wxBITMAP_TYPE_JPEG);
    //wxLogMessage(wxT("Je suis sauvegarde"));

}

void MyPanel::OnMirror(int id){
    *m_image = m_image->Mirror(id == ID_Mirror_hor);
    Refresh();
}

void MyPanel::OnBlur(int id){
    //m_image->Mirror(true);
    if(id == ID_Blur){
        *m_image = m_image->Blur(1);
    } else if(id == ID_Anti_Blur){
        *m_image = m_image->Blur(-10);
    }
    Refresh();
}

void MyPanel::OnRotate(){
    MyRotateDialog* d = new MyRotateDialog(this); //(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));
    int ok = d->ShowModal();
    wxSize size;
    int res = d->RadioBox1->GetSelection();
    switch(res) {
        case 0:
            *m_image = m_image->Rotate90();
            size = m_image->GetSize();
            this->GetParent()->SetClientSize(size);
            break;
        case 1:
            *m_image = m_image->Rotate180();
            size = m_image->GetSize();
            this->GetParent()->SetClientSize(size);
            break;
        case 2:
            *m_image = m_image->Rotate90(false);
            size = m_image->GetSize();
            this->GetParent()->SetClientSize(size);
            break;
        default:
            wxString s;
            s.sprintf("%d",res);
            wxLogMessage(s);
    }
    Refresh();
}

void MyPanel::OnNegatif(){
    m_image->negative();
    Refresh();
}

void MyPanel::OnDesaturate(){
    m_image->Desaturate();
    Refresh();
}

void MyPanel::OnSeuil(){
    MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
    dlg->ShowModal();
    m_image->Threshold(dlg->m_threshold->GetValue());
    Refresh();
}

void MyPanel::OnMirrorMain(int id){
    m_image->Mirroir(id == ID_Mirror_ver_main);
    Refresh();
}

void MyPanel::OnRotate90Main(){
    MyImage* m = m_image;
    m_image = m_image->Rotation90();
    if(m != nullptr){
        m->Destroy();
    }
    this->GetParent()->SetClientSize(m_image->GetSize());
    Refresh();
}

void MyPanel::OnPosterize(){
    m_image->posterize();
    Refresh();
}

void MyPanel::OnHistogramme(){
    int nb = m_image->histogramme();
    wxString s;
    s.sprintf("il y a %d couleurs sur cette image",nb);
    wxLogMessage(s);
    Refresh();
}








bool MyPanel::isImage(){
    return m_image != nullptr;
}

