/// <reference path="../../typings/angularjs/angular.d.ts" />
class BDecotexController
{
    static dependencies = ['$scope', 'BackendService', BDecotexController];
    private backendHandler: BackendService;
    private scope: ng.IScope;
    private callbackCounter: number;
    private txt:string;
    private nombres:Array<ModelFamily>;
    private waitingScreen: boolean;
    private messageScreen: boolean;

    constructor(scope: ng.IScope, BackendService: BackendService)
    {
        this.backendHandler = BackendService;
//        this.screenHandler = screenController;
        this.updateFamilyList();
        this.scope = scope;
        this.callbackCounter = 0;
        
//        this.scope.$watch(() => { return this.callbackCounter; }, (newValue, oldValue) => {
//            if (newValue !== oldValue) {
//                this.screenHandler.hideWaitingScreen();
//            }
//        });
    }

    public add()
    {
//        this.screenHandler.showWaitingScreen();
        this.backendHandler.addFamily(new ModelFamily(this.txt, this.txt)).then(
            result => {
                this.nombres.push(result.data);
                this.callbackCounter++;
            },
            result => {
                console.log(result);
                this.callbackCounter++;
            }
        );
    }
    
    public delete(id_family:number)
    {
        alert("Seguro que quieres borrar la familia con ID " + id_family);
//        this.screenHandler.showWaitingScreen();
        this.backendHandler.deleteFamily(id_family).then(
            result => {
                this.nombres.push(<ModelFamily>result.data);
                this.callbackCounter++;
            },
            result => {
                console.log(result);
                this.callbackCounter++;
            }
        );
    }
    
    private updateFamilyList(){
//        this.screenHandler.showWaitingScreen();
        this.backendHandler.getFamilies().then(
            result => {
                this.nombres = <Array<ModelFamily>> result.data;
                this.callbackCounter++;
            },
            result => {
                console.log(result);
                this.callbackCounter++;
            }
        );
    }
    
    public togleWaiting()
    {
        this.waitingScreen = !this.waitingScreen;
    }
    
    public togleMessage()
    {
        this.messageScreen = !this.messageScreen;
    }
}

// Register the controller with Angular
bdecotexApp.controller(
	'BDecotexController', BDecotexController.dependencies);
