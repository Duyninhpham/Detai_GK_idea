Hệ thống tưới cây thông minh
1. Giới thiệu
Hệ thống tưới cây thông minh là một giải pháp nhằm tự động hóa việc tưới tiêu cho cây trồng. Hệ thống sử dụng cảm biến độ ẩm đất để theo dõi tình trạng đất và tự động kích hoạt bơm nước khi đất khô. Ngoài ra, người dùng có thể theo dõi và điều khiển hệ thống thông qua giao diện Dashboard trên Node-RED, hỗ trợ điều khiển từ xa bằng điện thoại thông minh hoặc máy tính.

2. Đặt vấn đề
Nhu cầu thực tế:
Những người bận rộn thường quên tưới cây hoặc không thể theo dõi tình trạng đất thường xuyên, dẫn đến cây bị khô hạn hoặc úng nước. Hệ thống này giúp giải quyết vấn đề bằng cách tự động hóa hoàn toàn quy trình tưới nước.

Ứng dụng:
Các hộ gia đình trồng cây trong chậu hoặc khu vườn nhỏ.
Nông trại cần giải pháp tưới thông minh, tiết kiệm nước.

3. Mục tiêu dự án
Theo dõi độ ẩm của đất trong thời gian thực.
Tự động tưới nước khi đất khô.
Hiển thị thông tin độ ẩm đất và trạng thái bơm nước trên Dashboard.
Điều khiển bơm từ xa qua giao diện Dashboard hoặc điện thoại.

5. Phần cứng cần thiết
ESP32 Dev Board.
Cảm biến độ ẩm đất.
Relay Module (để điều khiển bơm nước).
Bơm nước nhỏ hoặc LED (nếu chỉ mô phỏng).
Nguồn điện phù hợp cho bơm.

6. Giao thức sử dụng
MQTT:
Gửi dữ liệu cảm biến từ ESP32 đến broker online.
Nhận lệnh điều khiển từ Dashboard.

Node-RED Dashboard:
Hiển thị dữ liệu độ ẩm đất.
Hiển thị trạng thái bơm nước.
Cho phép bật/tắt bơm thủ công.

7. Sơ đồ khối dự kiến
   ![SmartIrrigationSystem](https://github.com/user-attachments/assets/a29dc484-5d2b-4e5f-9382-e8492f882f48)
