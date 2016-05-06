<?php

$table = 7;
function ucfirst_utf8($str)
{
    return mb_substr(mb_strtoupper($str, 'utf-8'), 0, 1, 'utf-8') . mb_substr($str, 1, mb_strlen($str)-1, 'utf-8');
}
?>
    <style>
        body {
            font: 14pt 'Times New Roman';
        }

        p {
            margin: 0;
            padding: 0;
        }
    </style>

<?php
foreach ($items as $key => $data): ?>
    <?php
    if (!$data)
        continue;
    $args = $data['vars'];
    $local_args = $data['local_var'];
    ?>
    <h2 style="text-align: center">6.<?= $key ?> Функция <?= $data['name'] ?></h2><br>
    <p><strong>Назначение функции:</strong> <?= $data['description'] ?></p>
    <p><strong>Прототип</strong><strong> функции</strong><strong>:</strong> <?= $data['prototype'] ?></p>
    <?php if ($data['return']): ?>
        <p><strong>Возврат функции</strong>: <?= $data['return'] ?></p>
    <?php endif ?>
    <p><strong>Пример</strong><strong> вызова</strong><strong>
            функции</strong><strong>:</strong> <?= $data['example'] ?></p>


    <?php if ($args || $local_args): ?>
        <?php if ($args): ?>

            <p><strong>Описание формальных переменных функции:</strong> описание формальных переменных
                функции <?= $data['name'] ?>
                представлено в таблице <?= $table ?></p>
            <p><strong>Описание фактических параметров функции:</strong> описание фактических параметров
                функции <?= $data['name'] ?>
                представлено в таблице <?= $table ?></p>
        <?php endif ?>

        <?php if ($local_args): ?>
            <p><strong>Описание локальных переменных функции:</strong> описание локальных
                переменных
                функции <?= $data['name'] ?> представлено
                в таблице <?= $table ?></p>
        <?php endif ?>
        <br>
        <p style="text-align: right"><em>Таблица <?= $table ?>. Описание переменных
                функции <?= $data['name'] ?></em></p>
        <table border="1" style="border-collapse: collapse; text-align: center">
            <tbody>
            <tr>
                <td><strong>Вид параметра</strong></td>
                <td><strong>Имя переменной</strong></td>
                <td><strong>Тип переменной</strong></td>
                <td><strong>Назначение переменной</strong></td>
            </tr>
            <?php if ($args): ?>

                <?php foreach ($args as $keyArg => $item): ?>
                    <tr>
                        <?php if ($keyArg == 0): ?>
                            <td rowspan="<?= count($args) ?>"><strong>Формальные параметры</strong></td>
                        <?php endif ?>
                        <td><?= $item['name'] ?></td>
                        <td><?= $item['type'] ?></td>
                        <td><?= ucfirst_utf8($item['description']) ?></td>
                    </tr>
                <?php endforeach ?>

                <?php foreach ($args as $keyArg => $item): ?>
                    <tr>
                        <?php if ($keyArg == 0): ?>
                            <td rowspan="<?= count($args) ?>"><strong>Фактические параметры</strong></td>
                        <?php endif ?>
                        <td><?= $item['name'] ?></td>
                        <td><?= $item['type'] ?></td>
                        <td><?= ucfirst_utf8($item['description']) ?></td>
                    </tr>
                <?php endforeach ?>
            <?php endif ?>

            <?php if ($local_args): ?>
                <?php foreach ($local_args as $keyArg => $item): ?>
                    <tr>
                        <?php if ($keyArg == 0): ?>
                            <td rowspan="<?= count($local_args) ?>"><strong>Локальные переменные</strong></td>
                        <?php endif ?>
                        <td><?= $item['name'] ?></td>
                        <td><?= $item['type'] ?></td>
                        <td><?= ucfirst_utf8($item['description']) ?></td>
                    </tr>
                <?php endforeach ?>
            <?php endif ?>

            </tbody>
        </table>
        <? $table++ ?>
    <?php endif ?>
    <br>
<?php endforeach ?>