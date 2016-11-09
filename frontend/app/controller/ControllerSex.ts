class ControllerSex
{
    static dependencies = ['ServiceSexBackend', ControllerSex];
    private backendHandler: ServiceSexBackend;
    private sexList: Array<ModelSex>;
    private sexSelected: ModelSex;
    private gridOptions: any;
    private gridApi: uiGrid.IGridApi;
    
    constructor(serviceBakend: ServiceSexBackend)
    {
        this.backendHandler = serviceBakend;
        
        this.gridOptions = {
            columnDefs: [{ field: 'code', width: 100 }, { field: 'name' }],
            enableRowSelection: true,
            multiSelect: false,
            enableRowHeaderSelection: false, //not checkbox
            onRegisterApi: (api: uiGrid.IGridApi) => {
                this.gridApi = api;
            }
        }
        
        this.backendHandler.getAllSex((sexArray)=>{
            this.sexList = <Array<ModelSex>>sexArray;
            this.gridOptions.data = this.sexList;
            console.log("Sexos recibidos");
        });
    }

    protected editSex() {
        let selections = this.gridApi.selection.getSelectedGridRows();
        if (selections.length === 1){
            this.selectSex(selections[0].entity);
        } else {
            alert("Por favor selecciona un sexo");
        }
    }
    
    protected selectSex(sex: ModelSex){
        // Clone the object to edit to avoid modify the original
        this.sexSelected = (JSON.parse(JSON.stringify(sex)));
    }
    
    protected createNewSex(){
        this.sexSelected = new ModelSex();
    }
    
    protected saveSex(){
        if (this.sexSelected.id_sex != undefined){
            this.backendHandler.updateSex(this.sexSelected, ()=>{
                window.location.reload();
            });
        } else {
            this.backendHandler.createNewSex(this.sexSelected, (createdSex)=>{
                window.location.reload();
            });
        }
    }
    
    protected deleteSex(){
        this.backendHandler.deleteSexById(this.sexSelected.id_sex, ()=>{
            window.location.reload();
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerSex', ControllerSex.dependencies);
