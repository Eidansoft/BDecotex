<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');
require_once (dirname(__FILE__).'/../controller/ModelController.php.inc');
require_once (dirname(__FILE__).'/../controller/ControllerException.php.inc');

/**
 * Description of ModelView
 *
 * @author alex
 */
class ModelView extends BDecotexView{
    
    const GET_ALL_MODEL = 0;
    const GET_MODEL = 1;
    const CREATE_MODEL = 2;
    const DELETE_MODEL = 3;
    const UPDATE_MODEL = 4;

    protected $controller;
    
    public function __construct() {
        parent::__construct();
        $this->controller = new ModelController;
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute('GET', $this->model_url, ModelView::GET_ALL_MODEL);
            // {id} must be a number (\d+)
            $r->addRoute('GET', $this->model_url.'/{id:\d+}', ModelView::GET_MODEL);
            $r->addRoute('POST', $this->model_url, ModelView::CREATE_MODEL);
            $r->addRoute('DELETE', $this->model_url.'/{id:\d+}', ModelView::DELETE_MODEL);
            $r->addRoute('PUT', $this->model_url.'/{id:\d+}', ModelView::UPDATE_MODEL);
        });
        parent::setDispatcher($dispatcher);
    }
    
    protected function processHandler($handler, $vars) {
        $res = NULL;
        try {
            switch ($handler) {
                case ModelView::GET_MODEL:
                    $res = $this->controller->getById($vars['id']);
                    break;
                case ModelView::GET_ALL_MODEL:
                    $res = $this->controller->getAll();
                    break;
                case ModelView::CREATE_MODEL:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $model = new ModelDTO($data);
                    $res = $this->controller->createModel($model);
                    break;
                case ModelView::DELETE_MODEL:
                    $this->controller->delete($vars['id']);
                    break;
                case ModelView::UPDATE_MODEL:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $model = new ModelDTO($data);
                    $res = $this->controller->updateModel($vars['id'], $model);
                    break;
            }
            parent::returnSuccess($res);
        } catch (ControllerException $e) {
            $e->throwToClient();
        } catch (ValidateDtoException $e) {
            $e->throwToClient();
        }
    }

}
