class ControllerLine
{
    static dependencies = ['ServiceLineBackend', ControllerLine];
    private backendHandler: ServiceLineBackend;
    private lineList: Array<ModelLine>;
    private lineSelected: ModelLine;
    private gridOptions: any;
    private gridApi: uiGrid.IGridApi;
    
    constructor(serviceBakend: ServiceLineBackend) {
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
        
        this.backendHandler.getAllLines((linesArray)=>{
            this.lineList = <Array<ModelLine>>linesArray;
            this.gridOptions.data = this.lineList;
            console.log("Lineas recibidas");
        });
    }

    protected editFamily() {
        let selections = this.gridApi.selection.getSelectedGridRows();
        if (selections.length === 1){
            this.selectLine(selections[0].entity);
        } else {
            alert("Por favor selecciona una linea");
        }
    }

    protected selectLine(line: ModelLine){
        // Clone the object to edit to avoid modify the original
        this.lineSelected = (JSON.parse(JSON.stringify(line)));
    }
    
    protected createNewLine(){
        this.lineSelected = new ModelLine();
    }
    
    protected saveLine(){
        if (this.lineSelected.id_line != undefined){
            this.backendHandler.updateLine(this.lineSelected, ()=>{
                this.lineList = this.lineList.map(line=>{
                    let res = line;
                    if (line.id_line == this.lineSelected.id_line){
                        res = this.lineSelected;
                    }
                    return res;
                });
                console.log("Linea editada");
                this.lineSelected = undefined;
            });
        } else {
            this.backendHandler.createNewLine(this.lineSelected, (createdLine)=>{
                this.lineList.push(<ModelLine>createdLine);
                console.log("Linea nueva creada");
                this.lineSelected = undefined;
            });
        }
    }
    
    protected deleteLine(){
        this.backendHandler.deleteLineById(this.lineSelected.id_line, ()=>{
            this.lineList = this.lineList.filter(line=>{
                let res = true;
                if (line.id_line == this.lineSelected.id_line){
                    res = false;
                }
                return res;
            });
            this.gridOptions.data = this.lineList;
            console.log("Linea eliminada");
            this.lineSelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerLine', ControllerLine.dependencies);
