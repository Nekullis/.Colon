使い方

int count = 10;
std::string str = "Hello, World!";

jsonデータと同じ方法でデータを格納することができます。
DataTypes　data;
data = {
 {"count", count},
 {"str", str}
};
 
データの取得方法
登録名を指定し、Getメソッドで取得したい型を指定します。
std::cout << data["count"].Get<int>() << std::endl;
std::cout << data["str"].Get<std::string>() << std::endl;
 
注意
string型のデータを上書きする場合、文字列リテラルを使用するとエラーが発生します。
data["str"] = "Hello, World!"; // エラー

代わりにstd::stringを使用してください。
data["str"] = std::string("World");　// OK
