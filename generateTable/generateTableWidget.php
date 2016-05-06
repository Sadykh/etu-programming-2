<?php
namespace app\widgets\generateTable;

use yii\base\Widget;
use Yii;
use yii\helpers\VarDumper;

class generateTableWidget extends Widget
{
    public function run()
    {
        $alias = Yii::getAlias('@app');
        $file = file_get_contents($alias . '/widgets/generateTable/source');
        $data = explode('/*', $file);
        $goodData = [];
        foreach ($data as $item) {
            $goodData[] = $this->processStr($item);
        }
//        VarDumper::dump($goodData, 10, true);
        return $this->render('index', ['items' => $goodData]);
    }

    /**
     * Обработка каждой функции
     * @param $str
     * @return array|bool
     */
    public function processStr($str)
    {
        $data = [];

        $local_params = $this->between('//	@start_local_params', '//	@end_local_params', $str);
        $str = $this->between('@start', '@end', $str);

        $data['name'] = trim($this->between('@name', '@', $str));
        if (!$data['name'])
            return false;

        $data['description'] = trim($this->between('@description ', '@', $str));
        $data['prototype'] = trim($this->between('@prototype', '@', $str));
        $data['example'] = trim($this->between('@example', '@', $str));
        $data['local_var'] = $this->processLocalVars($local_params);

        $return = trim($this->after('@return', $str));
        if ($return)
            $data['return'] = $return;

        $vars = trim($this->between('@param', '@return', $str));
        if ($vars) {
            $data['vars'] = $vars;
            $data['vars'] = '@param ' . $data['vars'];
            $data['vars'] = $this->processVars($data['vars']);
        }

        return $data;
    }


    /**
     * Обработка имени функции
     * @param $str
     * @return string
     */
    public function processName($str)
    {
        $str = $this->before('=>', $str);
        $data = $this->after(' **', $str);

        if (!$data)
            $data = $this->after(' *', $str);

        if (!$data)
            $data = $this->after('	', $str);

        return trim($data);
    }

    /**
     * Обработка описания аргумента
     * @param $str
     * @return string
     */
    public function processVarDescription($str)
    {
        $data = $this->after("=>", $str);

        return trim($data);
    }

    /**
     * Обработка аргументов функции
     * @param $str
     * @return array|bool
     */
    public function processVars($str)
    {
        if (empty($str))
            return false;

        $str = explode('@param', $str);
        $data = [];
        foreach ($str as $item) {
            if ($item)
                $data[] = [
                    'source args' => trim($item),
                    'name' => $this->processName($item),
                    'description' => $this->processVarDescription($item),
                    'type' => $this->processType($item)];
        }
        return $data;
    }


    /**
     * Обработка типа аргумента функции
     * @param $str
     * @return string
     */
    public function processType($str)
    {
        $data = $this->before(' *', $str);
        if ($data)
            $data = $data . ' *';

        if (!$data)
            $data = $this->before('	', $str);

        return trim($data);
    }

    /**
     * Обработка локальных переменных
     * @param $str
     * @return array|bool
     */
    public function processLocalVars($str)
    {
        if (empty($str))
            return false;

        $str = explode(';;', $str);
        $data = [];
        foreach ($str as $item) {
            if (trim($item)) {
                $data[] = [
                    'source args' => trim($item),
                    'name' => $this->processLocalVarName($item),
                    'description' => $this->processLocalVarDescription($item),
                    'type' => $this->processLocalVarType($item)];
            }

        }
        return $data;
    }

    /**
     * Обработка имени локальной переменной
     * @param $str
     * @return string
     */
    public function processLocalVarName($str)
    {
        $preStr = $this->before(' =', $str);
        if ($preStr)
            $str = $preStr;
        else
            $str = $this->before(';', $str);

        $data = $this->after(' **', $str);

        if (!$data)
            $data = $this->after(' *', $str);

        if (!$data)
            $data = $this->after(' ', $str);

        return trim($data);
    }

    /**
     * Обработка описания локальной переменной
     * @param $str
     * @return string
     */
    public function processLocalVarDescription($str)
    {
        $data = $this->after("//", $str);

        return trim($data);
    }

    public function processLocalVarType($str)
    {
        $data = $this->before(' *', $str);
        if ($data)
            $data = $data . ' *';

        if (!$data)
            $data = $this->before(' ', $str);

        return trim($data);
    }

    public function after($after, $string)
    {
        if (!is_bool(strpos($string, $after)))
            return substr($string, strpos($string, $after) + strlen($after));
    }

    public function before($before, $string)
    {
        return substr($string, 0, strpos($string, $before));
    }


    public function between($after, $before, $string)
    {
        return self::before($before, self::after($after, $string));
    }
}