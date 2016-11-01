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
                this.sexList = this.sexList.map(sex=>{
                    let res = sex;
                    if (sex.id_sex == this.sexSelected.id_sex){
                        res = this.sexSelected;
                    }
                    return res;
                });
                console.log("Sexo editado");
                this.sexSelected = undefined;
            });
        } else {
            this.backendHandler.createNewSex(this.sexSelected, (createdSex)=>{
                this.sexList.push(<ModelSex>createdSex);
                console.log("Sexo nuevo creado");
                this.sexSelected = undefined;
            });
        }
    }
    
    protected deleteSex(){
        this.backendHandler.deleteSexById(this.sexSelected.id_sex, ()=>{
            this.sexList = this.sexList.filter(sex=>{
                let res = true;
                if (sex.id_sex == this.sexSelected.id_sex){
                    res = false;
                }
                return res;
            });
            console.log("Sexo eliminado");
            this.sexSelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerSex', ControllerSex.dependencies);
