class ControllerModel
{
    static dependencies = [ControllerModel];
    
    constructor()
    {
        
    }

}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerModel', ControllerModel.dependencies);
