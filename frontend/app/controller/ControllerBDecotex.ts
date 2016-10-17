class ControllerBDecotex
{
    static dependencies = ['PubSub', ControllerBDecotex];
    private pubsubHandler: any;

    constructor(PubSub: any){
        this.pubsubHandler = PubSub;
    }
    
    public test(){
        this.pubsubHandler.publish('SHOW_WAITING_SCREEN', true);
        console.log("TESTTT!!!!!");
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerBDecotex', ControllerBDecotex.dependencies);
