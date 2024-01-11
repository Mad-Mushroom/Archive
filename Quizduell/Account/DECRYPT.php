<html>
    <head>
        <title>Quizduell - Register</title>
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');

            $edkey = "FU625x3BYr2HIgTNzfkz76BdAGeoTOVg";

            function safeDecrypt(string $encrypted, string $key): string{
                $ciphering = "AES-128-CTR";
                $decryption_iv = '1234567891011121';
                $options = 0;
                $decryption_key = $key;

                $decryption=openssl_decrypt ($encrypted, $ciphering, 
                $decryption_key, $options, $decryption_iv);

                return $decryption;
            }
            function safeEncrypt(string $message, string $key): string{
                $ciphering = "AES-128-CTR";
 
                $iv_length = openssl_cipher_iv_length($ciphering);
                $options = 0;

                $encryption_iv = '1234567891011121';

                $encryption_key = $key;

                $encryption = openssl_encrypt($message, $ciphering,
                $encryption_key, $options, $encryption_iv);

                return $encryption;
            }
        ?>
    </head>
    <body>
        <form action="DECRYPT.php" method="post">
            <input type="text" name="text" placeholder="TEXT"/><br><br>
            <input type="submit" name="submit" value="DECRYPT" />
            <input type="submit" name="encrypt" value="ENCRYPT" />
        </form>

        <?php
            if(isset($_POST['submit'])) echo safeDecrypt($_POST['text'], $edkey);
            if(isset($_POST['encrypt'])) echo safeEncrypt($_POST['text'], $edkey);
        ?>
    </body>
</html>
