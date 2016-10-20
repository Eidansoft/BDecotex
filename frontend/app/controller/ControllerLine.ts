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

}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerLine', ControllerLine.dependencies);
