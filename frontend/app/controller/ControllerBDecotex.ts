class ControllerBDecotex
{
    static dependencies = [ControllerBDecotex];
    private waitingScreen;

    constructor(){
        this.waitingScreen = false;
    }
    
    public test(){
        console.log("TESTTT!!!!!");
        this.waitingScreen = !this.waitingScreen;
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerBDecotex', ControllerBDecotex.dependencies);
