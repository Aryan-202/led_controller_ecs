#ifndef WEB_CONTENT_H
#define WEB_CONTENT_H

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Energy Management System</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        :root {
            --primary: #2e7d32;
            --primary-light: #4caf50;
            --primary-dark: #1b5e20;
            --secondary: #f5f5f5;
            --text: #333;
            --text-light: #666;
            --bg: #ffffff;
            --card-bg: #f9f9f9;
            --shadow: rgba(0, 0, 0, 0.1);
            --success: #4caf50;
            --warning: #ff9800;
            --danger: #f44336;
            --info: #2196f3;
        }
        .dark-mode {
            --primary: #4caf50;
            --primary-light: #66bb6a;
            --primary-dark: #388e3c;
            --secondary: #424242;
            --text: #f5f5f5;
            --text-light: #bdbdbd;
            --bg: #303030;
            --card-bg: #424242;
            --shadow: rgba(0, 0, 0, 0.3);
        }
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        body {
            background-color: var(--bg);
            color: var(--text);
            transition: background-color 0.3s, color 0.3s;
        }
        .container {
            display: flex;
            min-height: 100vh;
        }
        .sidebar {
            width: 250px;
            background-color: var(--primary);
            color: white;
            padding: 20px 0;
            transition: all 0.3s;
        }
        .logo {
            text-align: center;
            padding: 20px 0;
            border-bottom: 1px solid rgba(255, 255, 255, 0.1);
            margin-bottom: 20px;
        }
        .logo h1 {
            font-size: 1.5rem;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        .logo i {
            font-size: 1.8rem;
        }
        .nav-links {
            list-style: none;
            padding: 0 15px;
        }
        .nav-links li {
            margin-bottom: 10px;
        }
        .nav-links a {
            display: flex;
            align-items: center;
            padding: 12px 15px;
            color: white;
            text-decoration: none;
            border-radius: 8px;
            transition: all 0.3s;
        }
        .nav-links a:hover, .nav-links a.active {
            background-color: var(--primary-dark);
        }
        .nav-links i {
            margin-right: 10px;
            font-size: 1.2rem;
        }
        .main-content {
            flex: 1;
            padding: 20px;
            overflow-y: auto;
        }
        .header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 30px;
            padding-bottom: 15px;
            border-bottom: 1px solid var(--shadow);
        }
        .header h2 {
            font-size: 1.8rem;
            color: var(--primary);
        }
        .connection-status {
            display: flex;
            align-items: center;
            gap: 8px;
            padding: 8px 16px;
            border-radius: 20px;
            background-color: var(--success);
            color: white;
            font-size: 0.9rem;
        }
        .connection-status.disconnected {
            background-color: var(--danger);
        }
        .status-dot {
            width: 8px;
            height: 8px;
            border-radius: 50%;
            background-color: white;
            animation: pulse 2s infinite;
        }
        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }
        .tab-content {
            display: none;
            animation: fadeIn 0.5s;
        }
        .tab-content.active {
            display: block;
        }
        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }
        .card {
            background-color: var(--card-bg);
            border-radius: 15px;
            box-shadow: 0 8px 16px var(--shadow);
            padding: 25px;
            margin-bottom: 25px;
            transition: transform 0.3s, box-shadow 0.3s;
            border-left: 4px solid var(--primary);
        }
        .card:hover {
            transform: translateY(-5px);
            box-shadow: 0 12px 20px var(--shadow);
        }
        .card-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 20px;
            padding-bottom: 15px;
            border-bottom: 1px solid var(--shadow);
        }
        .card-header h3 {
            font-size: 1.3rem;
            color: var(--primary);
        }
        .environment-info {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 20px;
            margin-bottom: 25px;
        }
        .env-card {
            background: linear-gradient(135deg, var(--primary-light), var(--primary));
            color: white;
            border-radius: 12px;
            padding: 20px;
            text-align: center;
            box-shadow: 0 4px 12px rgba(46, 125, 50, 0.3);
        }
        .env-card i {
            font-size: 2.5rem;
            margin-bottom: 10px;
        }
        .env-value {
            font-size: 2rem;
            font-weight: bold;
            margin: 10px 0;
        }
        .env-label {
            font-size: 0.9rem;
            opacity: 0.9;
        }
        .control-panel {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 20px;
        }
        .device-card {
            background-color: var(--card-bg);
            border-radius: 12px;
            box-shadow: 0 6px 12px var(--shadow);
            padding: 20px;
            text-align: center;
            transition: transform 0.3s;
            border-top: 3px solid var(--primary);
        }
        .device-card:hover {
            transform: translateY(-5px);
        }
        .device-icon {
            font-size: 2.5rem;
            color: var(--primary);
            margin-bottom: 15px;
        }
        .device-status {
            font-size: 1.2rem;
            margin-bottom: 15px;
            font-weight: 600;
        }
        .toggle-switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
            margin-bottom: 15px;
        }
        .toggle-switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: .4s;
            border-radius: 34px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider {
            background-color: var(--primary);
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }
        input:disabled + .slider {
            opacity: 0.5;
            cursor: not-allowed;
        }
        .mode-selector {
            display: flex;
            justify-content: center;
            gap: 10px;
            margin-top: 10px;
        }
        .mode-btn {
            padding: 8px 15px;
            border: none;
            border-radius: 20px;
            background-color: var(--secondary);
            color: var(--text);
            cursor: pointer;
            transition: all 0.3s;
            font-size: 0.85rem;
        }
        .mode-btn.active {
            background-color: var(--primary);
            color: white;
        }
        .info-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
            gap: 15px;
            margin-top: 20px;
        }
        .info-item {
            display: flex;
            flex-direction: column;
            padding: 15px;
            background-color: var(--secondary);
            border-radius: 8px;
        }
        .info-label {
            font-size: 0.9rem;
            color: var(--text-light);
            margin-bottom: 5px;
        }
        .info-value {
            font-size: 1.1rem;
            font-weight: 500;
        }
        .setting-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 15px 0;
            border-bottom: 1px solid var(--shadow);
        }
        .setting-info h4 {
            margin-bottom: 5px;
            color: var(--primary);
        }
        .setting-info p {
            font-size: 0.9rem;
            color: var(--text-light);
        }
        @media (max-width: 768px) {
            .container {
                flex-direction: column;
            }
            .sidebar {
                width: 100%;
                padding: 10px 0;
            }
            .nav-links {
                display: flex;
                justify-content: space-around;
            }
            .nav-links li {
                margin-bottom: 0;
            }
            .nav-links a {
                flex-direction: column;
                padding: 10px;
                font-size: 0.8rem;
            }
            .nav-links i {
                margin-right: 0;
                margin-bottom: 5px;
            }
            .environment-info {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="sidebar">
            <div class="logo">
                <h1><i class="fas fa-leaf"></i> EnergySmart</h1>
            </div>
            <ul class="nav-links">
                <li><a href="#" class="nav-link active" data-tab="home"><i class="fas fa-home"></i> Home Control</a></li>
                <li><a href="#" class="nav-link" data-tab="settings"><i class="fas fa-cog"></i> Settings</a></li>
            </ul>
        </div>
        <div class="main-content">
            <div class="header">
                <h2 id="page-title">Home Control</h2>
                <div class="connection-status" id="connection-status">
                    <span class="status-dot"></span>
                    <span>Connected</span>
                </div>
            </div>
            <div id="home" class="tab-content active">
            <!-- Add this to your existing HTML in the home tab -->
<div class="card">
    <div class="card-header">
        <h3>Voice Assistant</h3>
        <span><i class="fas fa-microphone"></i> Powered by Ollama</span>
    </div>
    <div style="padding: 20px;">
        <div style="display: flex; gap: 10px; margin-bottom: 15px;">
            <input type="text" id="voice-command" placeholder="Type your voice command..." style="flex: 1; padding: 12px; border: 1px solid #ddd; border-radius: 8px;">
            <button id="send-voice-command" style="padding: 12px 20px; background-color: var(--primary); color: white; border: none; border-radius: 8px; cursor: pointer;">
                <i class="fas fa-paper-plane"></i> Send
            </button>
        </div>
        <div id="voice-response" style="padding: 15px; background-color: var(--secondary); border-radius: 8px; min-height: 50px; font-size: 0.9rem;">
            Voice responses will appear here...
        </div>
        <div style="margin-top: 15px; font-size: 0.8rem; color: var(--text-light);">
            <p><strong>Try saying:</strong> "turn off light", "switch to auto mode", "what's the status"</p>
        </div>
    </div>
</div>
                <div class="card">
                    <div class="card-header">
                        <h3>System Status</h3>
                        <span>Last updated: <span id="last-updated">Just now</span></span>
                    </div>
                    <div class="environment-info">
                        <div class="env-card">
                            <i class="fas fa-lightbulb"></i>
                            <div class="env-value" id="led-state">OFF</div>
                            <div class="env-label">LED Status</div>
                        </div>
                        <div class="env-card">
                            <i class="fas fa-eye"></i>
                            <div class="env-value" id="motion-status">NO</div>
                            <div class="env-label">Motion Detected</div>
                        </div>
                        <div class="env-card">
                            <i class="fas fa-cog"></i>
                            <div class="env-value" id="system-mode">AUTO</div>
                            <div class="env-label">Control Mode</div>
                        </div>
                        <div class="env-card">
                            <i class="fas fa-wifi"></i>
                            <div class="env-value" id="wifi-status">ONLINE</div>
                            <div class="env-label">Connection</div>
                        </div>
                    </div>
                </div>
                <div class="card">
                    <div class="card-header">
                        <h3>LED Control</h3>
                        <span>Current Mode: <span id="current-mode-text">Auto (PIR)</span></span>
                    </div>
                    <div class="control-panel">
                        <div class="device-card">
                            <div class="device-icon">
                                <i class="fas fa-lightbulb"></i>
                            </div>
                            <h3>Smart LED</h3>
                            <div class="device-status" id="light-status">OFF</div>
                            <label class="toggle-switch">
                                <input type="checkbox" id="light-toggle">
                                <span class="slider"></span>
                            </label>
                            <div class="mode-selector">
                                <button class="mode-btn active" id="auto-mode-btn">Auto (PIR)</button>
                                <button class="mode-btn" id="manual-mode-btn">Manual</button>
                            </div>
                            <div style="margin-top: 15px; font-size: 0.9rem; color: var(--text-light);">
                                <p id="mode-help">PIR sensor controls LED automatically</p>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="card">
                    <div class="card-header">
                        <h3>Device Information</h3>
                    </div>
                    <div class="info-grid">
                        <div class="info-item">
                            <span class="info-label">LED Pin</span>
                            <span class="info-value">GPIO 2</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">PIR Pin</span>
                            <span class="info-value">GPIO 4</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">Update Rate</span>
                            <span class="info-value">2 seconds</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">Total Updates</span>
                            <span class="info-value" id="update-count">0</span>
                        </div>
                    </div>
                </div>
            </div>
            <div id="settings" class="tab-content">
                <div class="card">
                    <div class="card-header">
                        <h3>Display Settings</h3>
                    </div>
                    <div class="setting-item">
                        <div class="setting-info">
                            <h4>Dark Mode</h4>
                            <p>Switch between light and dark themes</p>
                        </div>
                        <label class="toggle-switch">
                            <input type="checkbox" id="darkmode-toggle">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
                <div class="card">
                    <div class="card-header">
                        <h3>About</h3>
                    </div>
                    <div class="info-grid">
                        <div class="info-item">
                            <span class="info-label">Device</span>
                            <span class="info-value">ESP32</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">Version</span>
                            <span class="info-value">1.0.0</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">Platform</span>
                            <span class="info-value">Arduino</span>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script>
        let updateCounter = 0;
        let currentMode = 'auto';

        // Voice command handling
document.getElementById('send-voice-command').addEventListener('click', function() {
    const command = document.getElementById('voice-command').value;
    if (command.trim() === '') return;

    const responseElement = document.getElementById('voice-response');
    responseElement.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Processing...';

    fetch('/voice?command=' + encodeURIComponent(command))
        .then(response => response.json())
        .then(data => {
            if (data.status === 'success') {
                responseElement.innerHTML = '<span style="color: var(--success)"><i class="fas fa-check-circle"></i> ' + data.message + '</span>';
                // Update the UI to reflect changes
                setTimeout(updateStatus, 500);
            } else {
                responseElement.innerHTML = '<span style="color: var(--danger)"><i class="fas fa-exclamation-circle"></i> ' + data.message + '</span>';
            }
        })
        .catch(error => {
            console.error('Voice command error:', error);
            responseElement.innerHTML = '<span style="color: var(--danger)"><i class="fas fa-exclamation-circle"></i> Error sending command</span>';
        });
});

// Allow pressing Enter to send command
document.getElementById('voice-command').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        document.getElementById('send-voice-command').click();
    }
});

        // Tab Navigation
        document.querySelectorAll('.nav-link').forEach(link => {
            link.addEventListener('click', function(e) {
                e.preventDefault();
                document.querySelectorAll('.nav-link').forEach(item => {
                    item.classList.remove('active');
                });
                document.querySelectorAll('.tab-content').forEach(tab => {
                    tab.classList.remove('active');
                });
                this.classList.add('active');
                const tabId = this.getAttribute('data-tab');
                document.getElementById(tabId).classList.add('active');
                document.getElementById('page-title').textContent = this.textContent.trim();
            });
        });

        // LED Toggle Control
        document.getElementById('light-toggle').addEventListener('change', function() {
            const state = this.checked ? 'ON' : 'OFF';
            fetch('/led?state=' + state)
                .then(response => response.text())
                .then(data => {
                    console.log('LED Response:', data);
                    updateLEDStatus(this.checked);
                })
                .catch(error => {
                    console.error('Error:', error);
                    this.checked = !this.checked;
                    showConnectionError();
                });
        });

        // Auto Mode Button
        document.getElementById('auto-mode-btn').addEventListener('click', function() {
            fetch('/mode?value=AUTO')
                .then(response => response.text())
                .then(data => {
                    console.log('Mode Response:', data);
                    setModeUI('auto');
                })
                .catch(error => {
                    console.error('Error:', error);
                    showConnectionError();
                });
        });

        // Manual Mode Button
        document.getElementById('manual-mode-btn').addEventListener('click', function() {
            fetch('/mode?value=MANUAL')
                .then(response => response.text())
                .then(data => {
                    console.log('Mode Response:', data);
                    setModeUI('manual');
                })
                .catch(error => {
                    console.error('Error:', error);
                    showConnectionError();
                });
        });

        // Set Mode UI
        function setModeUI(mode) {
            currentMode = mode;
            const autoBtn = document.getElementById('auto-mode-btn');
            const manualBtn = document.getElementById('manual-mode-btn');
            const toggle = document.getElementById('light-toggle');
            const modeText = document.getElementById('current-mode-text');
            const modeHelp = document.getElementById('mode-help');
            const systemMode = document.getElementById('system-mode');

            if (mode === 'auto') {
                autoBtn.classList.add('active');
                manualBtn.classList.remove('active');
                toggle.disabled = true;
                modeText.textContent = 'Auto (PIR)';
                modeHelp.textContent = 'PIR sensor controls LED automatically';
                systemMode.textContent = 'AUTO';
            } else {
                autoBtn.classList.remove('active');
                manualBtn.classList.add('active');
                toggle.disabled = false;
                modeText.textContent = 'Manual';
                modeHelp.textContent = 'Use toggle switch to control LED';
                systemMode.textContent = 'MANUAL';
            }
        }

        // Update LED Status Display
        function updateLEDStatus(isOn) {
            const statusElement = document.getElementById('light-status');
            const ledStateElement = document.getElementById('led-state');
            
            if (isOn) {
                statusElement.textContent = 'ON';
                statusElement.style.color = 'var(--success)';
                ledStateElement.textContent = 'ON';
            } else {
                statusElement.textContent = 'OFF';
                statusElement.style.color = 'var(--text)';
                ledStateElement.textContent = 'OFF';
            }
        }

        // Fetch Status from ESP32
        function updateStatus() {
            fetch('/status')
                .then(response => response.json())
                .then(data => {
                    // Update LED status
                    const toggle = document.getElementById('light-toggle');
                    toggle.checked = data.ledState == 1;
                    updateLEDStatus(data.ledState == 1);
                    
                    // Update motion detection
                    const motionElement = document.getElementById('motion-status');
                    if (data.motion == 1) {
                        motionElement.textContent = 'YES';
                        motionElement.parentElement.style.background = 
                            'linear-gradient(135deg, #ff9800, #f57c00)';
                    } else {
                        motionElement.textContent = 'NO';
                        motionElement.parentElement.style.background = 
                            'linear-gradient(135deg, var(--primary-light), var(--primary))';
                    }
                    
                    // Update mode
                    if (data.mode === 'manual') {
                        setModeUI('manual');
                    } else {
                        setModeUI('auto');
                    }
                    
                    // Update timestamp
                    const now = new Date();
                    document.getElementById('last-updated').textContent = 
                        now.toLocaleTimeString();
                    
                    // Update counter
                    updateCounter++;
                    document.getElementById('update-count').textContent = updateCounter;
                    
                    // Show connected status
                    const connStatus = document.getElementById('connection-status');
                    connStatus.classList.remove('disconnected');
                    connStatus.innerHTML = '<span class="status-dot"></span><span>Connected</span>';
                    document.getElementById('wifi-status').textContent = 'ONLINE';
                })
                .catch(error => {
                    console.error('Status fetch error:', error);
                    showConnectionError();
                });
        }

        // Show Connection Error
        function showConnectionError() {
            const connStatus = document.getElementById('connection-status');
            connStatus.classList.add('disconnected');
            connStatus.innerHTML = '<span class="status-dot"></span><span>Disconnected</span>';
            document.getElementById('wifi-status').textContent = 'OFFLINE';
        }

        // Dark Mode Toggle
        document.getElementById('darkmode-toggle').addEventListener('change', function() {
            if (this.checked) {
                document.body.classList.add('dark-mode');
                localStorage.setItem('darkMode', 'enabled');
            } else {
                document.body.classList.remove('dark-mode');
                localStorage.setItem('darkMode', 'disabled');
            }
        });

        // Load Dark Mode Preference
        function loadDarkMode() {
            const darkMode = localStorage.getItem('darkMode');
            if (darkMode === 'enabled') {
                document.body.classList.add('dark-mode');
                document.getElementById('darkmode-toggle').checked = true;
            }
        }

        // Initialize
        document.addEventListener('DOMContentLoaded', function() {
            loadDarkMode();
            updateStatus();
            setInterval(updateStatus, 2000); // Update every 2 seconds
        });
    </script>
</body>
</html>
)rawliteral";

#endif