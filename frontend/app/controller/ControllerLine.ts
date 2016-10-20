class ControllerLine
{
    static dependencies = ['ServiceLineBackend', ControllerLine];
    private backendHandler: ServiceLineBackend;
    private lineList: Array<ModelLine>;
    private lineSelected: ModelLine;
    
    constructor(serviceBakend: ServiceLineBackend)
    {
        this.backendHandler = serviceBakend;
        
        this.backendHandler.getAllLines((linesArray)=>{
            this.lineList = <Array<ModelLine>>linesArray;
            console.log("Lineas recibidas");
        });
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
            console.log("Linea eliminada");
            this.lineSelected = undefined;
        });
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerLine', ControllerLine.dependencies);
