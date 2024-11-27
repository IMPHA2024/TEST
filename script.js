const menuBtn = document.querySelector('.menu-btn');
const navLinks = document.querySelector('.nav-links');

menuBtn.addEventListener('click', () => {
    navLinks.classList.toggle('active');
}); 

const toggleCodeBtn = document.getElementById('toggleCodeBtn');
const codeContainer = document.getElementById('codeContainer');
const codeDisplay = document.getElementById('codeDisplay');

// 加载 C++ 文件
fetch("BT.cpp") // 确保 BT.cpp 文件在正确的路径下
    .then(response => {
        if (!response.ok) {
            throw new Error('网络响应不正常');
        }
        return response.text();
    })
    .then(data => {
        codeDisplay.textContent = data; // 显示文件内容
    })
    .catch(error => {
        console.error('加载 C++ 文件时出错:', error);
    });

// 切换代码显示状态
toggleCodeBtn.addEventListener('click', () => {
    if (codeContainer.style.display === 'none') {
        codeContainer.style.display = 'block'; // 显示代码
    } else {
        codeContainer.style.display = 'none'; // 隐藏代码
    }
});
