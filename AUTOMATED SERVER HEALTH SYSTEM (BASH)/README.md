# Linux Server Health Monitor

A lightweight Bash script that monitors a Linux server's health — CPU, RAM, disk usage, and failed SSH login attempts — and sends real-time alerts via Telegram when thresholds are crossed. Runs automatically via `cron`.

##  Features

- Checks **CPU**, **RAM**, and **disk usage** in real time
- Detects **failed SSH login attempts** (basic brute-force detection) from `/var/log/auth.log`
- Logs the **top 5 resource-heavy processes** when an alert triggers
- Sends instant **Telegram alerts** when any metric crosses a configurable threshold
- Writes daily timestamped logs to `~/monitor_logs/`
- Runs automatically every 5 minutes via `cron` — zero manual intervention

##  Tech Used

- Bash scripting
- Linux system commands: `top`, `free`, `df`, `ps`, `grep`
- `cron` for scheduling
- Telegram Bot API (via `curl`) for alerting

##  Project Structure

```
.
├── monitor.sh      # main script
└── README.md
```

## 🚀 Setup & Usage

### 1. Clone and give execute permission
```bash
git clone https://github.com/<your-username>/linux-health-monitor.git
cd linux-health-monitor
chmod +x monitor.sh
```

### 2. Run it manually
```bash
./monitor.sh
```

### 3. (Optional) Enable Telegram alerts
1. Create a bot via [@BotFather](https://t.me/BotFather) on Telegram and grab the **bot token**.
2. Get your **chat ID** by messaging the bot, then visiting:
   `https://api.telegram.org/bot<YourBotToken>/getUpdates`
3. Open `monitor.sh` and fill in:
   ```bash
   TELEGRAM_BOT_TOKEN="your-token-here"
   TELEGRAM_CHAT_ID="your-chat-id-here"
   ```

### 4. Automate with cron (runs every 5 minutes)
```bash
crontab -e
```
Add this line:
```
*/5 * * * * /full/path/to/monitor.sh
```

## ⚙️ Configuration

Thresholds can be adjusted at the top of `monitor.sh`:

```bash
CPU_THRESHOLD=80
RAM_THRESHOLD=80
DISK_THRESHOLD=80
LOGIN_FAIL_THRESHOLD=5
```

## 📋 Sample Log Output

```
2026-07-18 10:05:01 | CPU: 42% | RAM: 55% | DISK: 61% | Failed SSH logins: 2
2026-07-18 10:10:01 | CPU: 91% | RAM: 60% | DISK: 61% | Failed SSH logins: 2
2026-07-18 10:10:01 | ALERT TRIGGERED:
2026-07-18 10:10:01 |  High CPU usage: 91%
```

##  Why I Built This

Most servers fail silently until it's too late. This project simulates a basic version of what real monitoring tools (like Nagios, Datadog, or Prometheus) do at a small scale — parsing system metrics, applying thresholds, and pushing real-time alerts — while sticking to plain Bash and core Linux utilities.

##  Future Improvements

- [ ] Dockerize for easy deployment across servers
- [ ] Export logs to CSV and visualize with Python/Matplotlib
- [ ] Add self-healing (e.g., auto-restart a crashed service)
- [ ] Support monitoring multiple remote servers via SSH
- [ ] Email alerts as a fallback to Telegram

## 📄 License

MIT License — free to use and modify.
